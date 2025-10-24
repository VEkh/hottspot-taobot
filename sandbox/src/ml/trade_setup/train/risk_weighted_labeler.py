import ml.utils as u
import numpy as np
import pandas as pd


class RiskWeightedLabeler:
    """
    Generate labels based on risk-adjusted performance rather than raw P&L.

    The key insight: We care more about avoiding catastrophic losses
    than maximizing gains.
    """

    def __init__(
        self,
        catastrophic_loss_percentile=5.0,
        confidence_percentile=75.0,
        max_drawdown_weight=2.0,
    ):
        self.catastrophic_loss_percentile = catastrophic_loss_percentile
        self.catastrophic_loss_threshold = None
        self.confidence_percentile = confidence_percentile
        self.confidence_scale = 0.0
        self.max_drawdown_weight = max_drawdown_weight
        self.original_labels = pd.DataFrame()

    def generate_labels(self, original_labels=pd.DataFrame()):
        self.original_labels = original_labels
        self.__fit_catastrophic_threshold()
        self.__analyze_drawdown_distribution()

        results = []
        risk_diffs_for_scale = []

        for market_session_id, group in self.original_labels.groupby(
            "market_session_id"
        ):
            max_drawdowns = {}
            profit_loss_percents = {}
            scores = {}

            for _, row in group.iterrows():
                reverse_percentile_id = row["reverse_percentile_id"]
                profit_loss_percent = row["profit_loss_percent"]
                max_drawdown_percent = row["max_drawdown_percent"]

                risk_score = self.__calculate_risk_score(
                    max_drawdown_percent=max_drawdown_percent,
                    profit_loss_percent=profit_loss_percent,
                )

                scores[reverse_percentile_id] = risk_score
                profit_loss_percents[reverse_percentile_id] = profit_loss_percent
                max_drawdowns[reverse_percentile_id] = max_drawdown_percent

            if len(scores) < 2:
                continue

            # Lower risk score is better / safer
            better_reverse_percentile_id = min(scores, key=scores.get)
            worse_reverse_percentile_id = max(scores, key=scores.get)

            # Confidcence: How much better is the better choice
            risk_score_difference = (
                scores[worse_reverse_percentile_id]
                - scores[better_reverse_percentile_id]
            )

            risk_diffs_for_scale.append(risk_score_difference)

            results.append(
                {
                    "is_catastrophic_avoided": any(
                        pl < self.catastrophic_loss_threshold
                        for pl in profit_loss_percents.values()
                    ),
                    "market_session_id": market_session_id,
                    "profit_loss_percent_1": profit_loss_percents.get(1, None),
                    "profit_loss_percent_2": profit_loss_percents.get(2, None),
                    "reverse_percentile_id": better_reverse_percentile_id,
                    "risk_score_1": scores.get(1, None),
                    "risk_score_2": scores.get(2, None),
                    "risk_score_difference": risk_score_difference,
                }
            )

        self.confidence_scale = self.__calculate_confidence_scale(risk_diffs_for_scale)

        for result in results:
            risk_score_difference = result["risk_score_difference"]
            result["confidence"] = min(
                risk_score_difference / self.confidence_scale, 1.0
            )

        risk_weighted_labels = pd.DataFrame(results)

        u.ascii.puts(
            f"Generated {len(risk_weighted_labels)} risk-weighted labels",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts("Label distribution:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            risk_weighted_labels["reverse_percentile_id"].value_counts().to_string(),
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Catastrophic losses avoided: {risk_weighted_labels['is_catastrophic_avoided'].sum()}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Average confidence: {risk_weighted_labels['confidence'].mean():.3f}",
            u.ascii.MAGENTA,
            print_end="",
        )

        return risk_weighted_labels

    def __analyze_drawdown_distribution(self):
        all_drawdowns = self.original_labels.get(
            "max_drawdown_percent", pd.Series([0] * len(self.original_labels))
        ).values

        u.ascii.puts(f"Drawdown Distribution:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"  Mean: {np.mean(all_drawdowns):.2f}%", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"  95th percentile: {np.percentile(all_drawdowns, 95):.2f}%",
            u.ascii.MAGENTA,
        )

    def __calculate_confidence_scale(self, risk_score_differences):
        risk_score_differences = np.array(risk_score_differences)
        scale = np.percentile(risk_score_differences, self.confidence_percentile)

        if scale <= 0.0:
            u.ascii.puts(
                f"Warning: Calculated confidence scale is {scale:.2f}, using default of 50.0"
            )

        u.ascii.puts(f"Confidence Scale Calculation:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(f"  Risk Difference Distribution:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"    Mean: {np.mean(risk_score_differences):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    Median: {np.median(risk_score_differences):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    Std: {np.std(risk_score_differences):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    25th percentile: {np.percentile(risk_score_differences, 25):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    75th percentile: {np.percentile(risk_score_differences, 75):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    90th percentile: {np.percentile(risk_score_differences, 90):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Using {self.confidence_percentile}th percentile as scale: {scale:.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  This means {self.confidence_percentile}% of cases will have confidence ≤ 1.0",
            u.ascii.MAGENTA,
        )

        return scale

    def __calculate_risk_score(self, max_drawdown_percent=0.0, profit_loss_percent=0.0):
        """
        Calculate a risk-adjusted score for a trade.

        Lower scores are better (less risky).
        Heavily penalizes both negative P&L and large drawdowns.
        """

        if profit_loss_percent < self.catastrophic_loss_threshold:
            catastrophic_penalty = 100.0 * abs(profit_loss_percent)
        else:
            catastrophic_penalty = 0.0

        # Standard loss/gain component
        # Negative because we want lower scores for better outcomes
        profit_loss_score = -profit_loss_percent

        # Drawdown component (always positive, always bad)
        max_drawdown_score = abs(max_drawdown_percent) * self.max_drawdown_weight

        risk_score = profit_loss_score + max_drawdown_score + catastrophic_penalty

        return risk_score

    def __fit_catastrophic_threshold(self):
        all_profit_losses = self.original_labels["profit_loss_percent"].values

        self.catastrophic_loss_threshold = np.percentile(
            all_profit_losses,
            self.catastrophic_loss_percentile,
        )

        u.ascii.puts(f"P&L Distribution:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"  Mean: {np.mean(all_profit_losses):.2f}%", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"  Std: {np.std(all_profit_losses):.2f}%", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"  Min: {np.min(all_profit_losses):.2f}%", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(f"  Max: {np.max(all_profit_losses):.2f}%", u.ascii.MAGENTA)

        u.ascii.puts(
            f"Catastrophic loss threshold set at: {self.catastrophic_loss_threshold:.2f}%",
            u.ascii.MAGENTA,
            print_end="",
        )

        u.ascii.puts(
            f"(Worst {self.catastrophic_loss_percentile}% percent of outcomes)",
            u.ascii.MAGENTA,
        )
