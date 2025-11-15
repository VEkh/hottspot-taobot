from tabulate import tabulate
import ml.utils as u
import numpy as np
import pandas as pd


class LabelExtractor:
    def __init__(self, confidence_percentile=75.0):
        self.confidence_percentile = confidence_percentile
        self.confidence_scale = 0.0
        self.original_labels = pd.DataFrame()

    def transform(self, original_labels):
        u.ascii.puts(f"\n{'='*60}", u.ascii.CYAN, print_end="")
        u.ascii.puts("🏷️  Extracting Multi-Class Labels", u.ascii.CYAN, print_end="")
        u.ascii.puts(f"{'='*60}", u.ascii.CYAN)

        self.original_labels = original_labels.copy()
        self._analyze_profit_loss_distribution()

        results = []
        profit_loss_spreads = []

        for market_session_id, group in self.original_labels.groupby(
            "market_session_id"
        ):
            profit_loss_percents = dict(
                zip(group["trade_setup_id"], group["profit_loss_percent"])
            )

            if len(profit_loss_percents) < 2:
                u.ascii.puts(
                    f"⚠️  Session {market_session_id} has only {len(profit_loss_percents)} trade_setups, skipping",
                    u.ascii.YELLOW,
                )

                continue

            best_row = group.loc[group["profit_loss_percent"].idxmax()]

            profit_loss_values = list(profit_loss_percents.values())
            profit_loss_spread = max(profit_loss_values) - min(profit_loss_values)
            profit_loss_spreads.append(profit_loss_spread)

            results.append(
                {
                    "market_session_id": market_session_id,
                    "market_session_opened_at": best_row["market_session_opened_at"],
                    "profit_loss_percent": best_row["profit_loss_percent"],
                    "profit_loss_spread": profit_loss_spread,
                    "reverse_percentile_id": best_row["reverse_percentile_id"],
                    "trade_setup_id": best_row["trade_setup_id"],
                }
            )

        self.confidence_scale = self._calculate_confidence_scale(profit_loss_spreads)

        for result in results:
            result["confidence"] = min(
                result["profit_loss_spread"] / self.confidence_scale, 1.0
            )

        labels = pd.DataFrame(results)
        self._print_label_summary(labels)

        return labels

    def _analyze_profit_loss_distribution(self):
        all_profit_losses = self.original_labels["profit_loss_percent"].values

        u.ascii.puts(f"Profit Loss Distribution:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"  Mean: {np.mean(all_profit_losses):.2f}%",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Std: {np.std(all_profit_losses):.2f}%",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Max: {np.max(all_profit_losses):.2f}%",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(f"  Min: {np.min(all_profit_losses):.2f}%", u.ascii.MAGENTA)

    def _calculate_confidence_scale(self, profit_loss_spreads):
        profit_loss_spreads = np.array(profit_loss_spreads)
        scale = np.percentile(profit_loss_spreads, self.confidence_percentile)

        if scale <= 0.0:
            u.ascii.puts(
                f"Warning: Calculated confidence scale is {scale:.2f}, using default of 50.0"
            )
            scale = 50.0

        u.ascii.puts(f"Confidence Scale Calculation:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"  Profit Loss Spread Distribution:", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"    Mean: {np.mean(profit_loss_spreads):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    Median: {np.median(profit_loss_spreads):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    Std: {np.std(profit_loss_spreads):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    25th percentile: {np.percentile(profit_loss_spreads, 25):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    75th percentile: {np.percentile(profit_loss_spreads, 75):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"    90th percentile: {np.percentile(profit_loss_spreads, 90):.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Using {self.confidence_percentile}th percentile as scale: {scale:.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Sessions with P&L spread ≥ {scale:.2f}% will have confidence = 1.0",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  ~{100 - self.confidence_percentile:.0f}% of sessions will have max confidence",
            u.ascii.MAGENTA,
        )

        return scale

    def _print_label_summary(self, labels):
        u.ascii.puts(
            f"✔️ Generated {len(labels)} labels (one per session)",
            u.ascii.GREEN,
        )

        u.ascii.puts("📊 Trade Setup Distribution:", u.ascii.MAGENTA)
        setup_dist = labels["trade_setup_id"].value_counts().sort_index()
        total = len(labels)

        dist_table = []
        for ts_id, count in setup_dist.items():
            dist_table.append(
                {
                    "trade_setup_id": ts_id,
                    "count": count,
                    "percentage": f"{count/total*100:.1f}%",
                }
            )

        u.ascii.puts(
            tabulate(dist_table, headers="keys", tablefmt="psql"), u.ascii.MAGENTA
        )

        u.ascii.puts("📊 Confidence Statistics:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"  Mean:   {labels['confidence'].mean():.3f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Median: {labels['confidence'].median():.3f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Std:    {labels['confidence'].std():.3f}", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"  Min:    {labels['confidence'].min():.3f}", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(f"  Max:    {labels['confidence'].max():.3f}", u.ascii.MAGENTA)

        u.ascii.puts(
            "\n📊 Profit Loss Spread Statistics:", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"  Mean:   {labels['profit_loss_spread'].mean():.2f}%",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Median: {labels['profit_loss_spread'].median():.2f}%",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Std:    {labels['profit_loss_spread'].std():.2f}%",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Min:    {labels['profit_loss_spread'].min():.2f}%",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Max:    {labels['profit_loss_spread'].max():.2f}%", u.ascii.MAGENTA
        )

        u.ascii.puts("📊 Confidence by Trade Setup:", u.ascii.MAGENTA, print_end="")
        confidence_by_setup = (
            labels.groupby("trade_setup_id")["confidence"]
            .agg(["count", "mean", "std", "min", "max"])
            .reset_index()
        )
        u.ascii.puts(
            tabulate(
                confidence_by_setup, headers="keys", tablefmt="psql", showindex=False
            ),
            u.ascii.MAGENTA,
        )
