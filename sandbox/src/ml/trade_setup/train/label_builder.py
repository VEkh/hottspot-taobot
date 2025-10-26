import ml.utils as u
import numpy as np
import pandas as pd


class LabelBuilder:
    def __init__(self, confidence_percentile=75.0):
        self.confidence_percentile = confidence_percentile
        self.confidence_scale = 0.0
        self.original_labels = pd.DataFrame()

    def build(self, original_labels=pd.DataFrame()):
        self.original_labels = original_labels
        self.__analyze_profit_loss_distribution()

        results = []
        profit_loss_diffs_for_scale = []

        for market_session_id, group in self.original_labels.groupby(
            "market_session_id"
        ):
            profit_loss_percents = {}

            for _, row in group.iterrows():
                reverse_percentile_id = row["reverse_percentile_id"]
                profit_loss_percent = row["profit_loss_percent"]
                profit_loss_percents[reverse_percentile_id] = profit_loss_percent

            if len(profit_loss_percents) < 2:
                continue

            better_reverse_percentile_id = max(
                profit_loss_percents, key=profit_loss_percents.get
            )

            worse_reverse_percentile_id = min(
                profit_loss_percents, key=profit_loss_percents.get
            )

            profit_loss_difference = abs(
                profit_loss_percents[better_reverse_percentile_id]
                - profit_loss_percents[worse_reverse_percentile_id]
            )

            profit_loss_diffs_for_scale.append(profit_loss_difference)

            results.append(
                {
                    "market_session_id": market_session_id,
                    "market_session_opened_at": group.iloc[0][
                        "market_session_opened_at"
                    ],
                    "profit_loss_difference": profit_loss_difference,
                    "profit_loss_percent_1": profit_loss_percents.get(1, None),
                    "profit_loss_percent_2": profit_loss_percents.get(2, None),
                    "reverse_percentile_id": better_reverse_percentile_id,
                }
            )

        self.confidence_scale = self.__calculate_confidence_scale(
            profit_loss_diffs_for_scale
        )

        for result in results:
            profit_loss_difference = result["profit_loss_difference"]

            result["confidence"] = min(
                profit_loss_difference / self.confidence_scale, 1.0
            )

        labels = pd.DataFrame(results)

        u.ascii.puts(
            f"Generated {len(labels)} Profit Loss-Based labels",
            u.ascii.MAGENTA,
        )

        u.ascii.puts("Label Distribution:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            labels["reverse_percentile_id"].value_counts().to_string(),
            u.ascii.MAGENTA,
        )

        u.ascii.puts(
            f"Average Confidence: {labels['confidence'].mean():.3f}",
            u.ascii.MAGENTA,
            print_end="",
        )

        u.ascii.puts(
            f"Average Profit Loss Difference: {labels['profit_loss_difference'].mean():.3f}",
            u.ascii.MAGENTA,
            print_end="",
        )

        u.ascii.puts("Confidence By Class:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            labels.groupby("reverse_percentile_id")["confidence"]
            .describe()
            .to_string(),
            u.ascii.MAGENTA,
        )

        return labels

    def __analyze_profit_loss_distribution(self):
        all_profit_losses = self.original_labels["profit_loss_percent"].values

        u.ascii.puts(f"Profit Loss Distribution:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"  Mean: {np.mean(all_profit_losses):.2f}%", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"  Std: {np.std(all_profit_losses):.2f}%", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"  Max: {np.max(all_profit_losses):.2f}%", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(f"  Min: {np.min(all_profit_losses):.2f}%", u.ascii.MAGENTA)

    def __calculate_confidence_scale(self, profit_loss_differences):
        profit_loss_differences = np.array(profit_loss_differences)
        scale = np.percentile(profit_loss_differences, self.confidence_percentile)

        if scale <= 0.0:
            u.ascii.puts(
                f"Warning: Calculated confidence scale is {scale:.2f}, using default of 50.0"
            )

        u.ascii.puts(f"Confidence Scale Calculation:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"  Profit Loss Difference Distribution:", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"    Mean: {np.mean(profit_loss_differences):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    Median: {np.median(profit_loss_differences):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    Std: {np.std(profit_loss_differences):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    25th percentile: {np.percentile(profit_loss_differences, 25):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    75th percentile: {np.percentile(profit_loss_differences, 75):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    90th percentile: {np.percentile(profit_loss_differences, 90):.2f}",
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
