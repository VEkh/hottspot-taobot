"""
Analyze whether sp_id=3 and sp_id=4 are redundant by comparing their
profit_loss_percent performance head-to-head across all sessions.
"""

import pandas as pd
import numpy as np
from tabulate import tabulate
import ml.utils as u


class TradeSetupRedundancyAnalyzer:
    def __init__(self, db_conn, market_session_ids):
        self.db_conn = db_conn
        self.market_session_ids = market_session_ids
        self.performances = None
        self.pivot_data = None

    def load_all_performances(self):
        """Load performances for ALL trade_setups (no sp_id filter)"""
        u.ascii.puts("📊 Loading All Trade Setup Performances", u.ascii.CYAN)

        with self.db_conn.conn.cursor() as cursor:
            query = """
            with session_performances as (
              select
                market_sessions.open_period,
                market_session_performances.market_session_id,
                lower(market_sessions.open_period) as market_session_opened_at,
                market_session_performances.profit_loss_percent,
                trade_setups.reverse_percentile_id,
                trade_setups.stop_profit_id,
                market_session_performances.trade_setup_id
              from
                market_sessions
                join market_session_performances on market_session_performances.market_session_id = market_sessions.id
                join trade_setups on trade_setups.id = market_session_performances.trade_setup_id
              where
                market_sessions.id = any(%(market_session_ids)s)
            )
            select
              market_session_id,
              market_session_opened_at::text as market_session_opened_at,
              profit_loss_percent,
              reverse_percentile_id as rp_id,
              stop_profit_id as sp_id,
              trade_setup_id
            from
              session_performances
            order by
              open_period asc
            """

            cursor.execute(query, {"market_session_ids": self.market_session_ids})

            columns = [column.name for column in cursor.description]
            rows = cursor.fetchall()

        self.performances = pd.DataFrame(rows, columns=columns)

        u.ascii.puts(
            f"✅ Loaded {len(self.performances)} performance records", u.ascii.GREEN
        )
        u.ascii.puts(
            f"   Sessions: {self.performances['market_session_id'].nunique()}",
            u.ascii.GREEN,
        )
        u.ascii.puts(
            f"   Trade Setups: {self.performances['trade_setup_id'].nunique()}",
            u.ascii.GREEN,
        )

        return self.performances

    def pivot_by_sp_id(self):
        """Pivot data so each row is a session with columns for each sp_id's performance"""
        u.ascii.puts("\n🔄 Pivoting Data by sp_id", u.ascii.CYAN)

        # Create pivot: market_session_id x rp_id -> sp_id columns
        pivot = self.performances.pivot_table(
            index=["market_session_id", "rp_id"],
            columns="sp_id",
            values="profit_loss_percent",
            aggfunc="first",  # Should only be one value per combination
        ).reset_index()

        # Rename columns for clarity
        pivot.columns.name = None
        sp_cols = [col for col in pivot.columns if isinstance(col, int)]
        rename_dict = {col: f"sp_{col}_pl" for col in sp_cols}
        pivot = pivot.rename(columns=rename_dict)

        self.pivot_data = pivot

        u.ascii.puts(f"✅ Pivoted to {len(self.pivot_data)} rows", u.ascii.GREEN)
        u.ascii.puts(f"   Columns: {list(self.pivot_data.columns)}", u.ascii.GREEN)

        return self.pivot_data

    def analyze_head_to_head(self):
        """Compare sp_id=3 vs sp_id=4 head-to-head for each rp_id"""
        u.ascii.puts("\n⚔️  Head-to-Head Analysis: sp_id=3 vs sp_id=4", u.ascii.CYAN)

        results = []

        for rp_id in sorted(self.pivot_data["rp_id"].unique()):
            subset = self.pivot_data[self.pivot_data["rp_id"] == rp_id].copy()

            # Filter to sessions where both sp_id=3 and sp_id=4 exist
            subset = subset.dropna(subset=["sp_3_pl", "sp_4_pl"])

            if len(subset) == 0:
                u.ascii.puts(f"⚠️  No data for rp_id={rp_id}", u.ascii.YELLOW)
                continue

            # Calculate differences
            subset["diff"] = subset["sp_3_pl"] - subset["sp_4_pl"]

            # Win rates
            sp3_wins = (subset["diff"] > 0).sum()
            sp4_wins = (subset["diff"] < 0).sum()
            ties = (subset["diff"] == 0).sum()
            total = len(subset)

            # Average advantage when each wins
            sp3_avg_advantage = (
                subset[subset["diff"] > 0]["diff"].mean() if sp3_wins > 0 else 0
            )
            sp4_avg_advantage = (
                -subset[subset["diff"] < 0]["diff"].mean() if sp4_wins > 0 else 0
            )

            # Overall statistics
            mean_diff = subset["diff"].mean()
            median_diff = subset["diff"].median()
            std_diff = subset["diff"].std()

            results.append(
                {
                    "rp_id": rp_id,
                    "sessions": total,
                    "sp3_wins": sp3_wins,
                    "sp3_win_rate": sp3_wins / total * 100,
                    "sp4_wins": sp4_wins,
                    "sp4_win_rate": sp4_wins / total * 100,
                    "ties": ties,
                    "tie_rate": ties / total * 100,
                    "sp3_avg_advantage": sp3_avg_advantage,
                    "sp4_avg_advantage": sp4_avg_advantage,
                    "mean_diff": mean_diff,
                    "median_diff": median_diff,
                    "std_diff": std_diff,
                }
            )

        results_df = pd.DataFrame(results)

        # Print detailed results
        for _, row in results_df.iterrows():
            u.ascii.puts(f"\n{'='*70}", u.ascii.MAGENTA)
            u.ascii.puts(f"rp_id = {row['rp_id']}", u.ascii.MAGENTA)
            u.ascii.puts(f"{'='*70}", u.ascii.MAGENTA)

            print(f"Total Sessions: {row['sessions']}")
            print(f"\nWin Rates:")
            print(f"  sp_id=3 wins: {row['sp3_wins']} ({row['sp3_win_rate']:.1f}%)")
            print(f"  sp_id=4 wins: {row['sp4_wins']} ({row['sp4_win_rate']:.1f}%)")
            print(f"  Ties:         {row['ties']} ({row['tie_rate']:.1f}%)")

            print(f"\nAverage Advantage When Winning:")
            print(f"  sp_id=3: {row['sp3_avg_advantage']:+.2f}%")
            print(f"  sp_id=4: {row['sp4_avg_advantage']:+.2f}%")

            print(f"\nOverall Difference (sp_id=3 - sp_id=4):")
            print(f"  Mean:   {row['mean_diff']:+.2f}%")
            print(f"  Median: {row['median_diff']:+.2f}%")
            print(f"  Std:    {row['std_diff']:.2f}%")

        return results_df

    def analyze_optimal_frequency(self):
        """Determine how often each sp_id appears as optimal across ALL trade_setups"""
        u.ascii.puts("\n🏆 Optimal Strategy Frequency Analysis", u.ascii.CYAN)

        # For each session, find which trade_setup_id (sp_id) had best P&L
        optimal_by_session = []

        for session_id in self.performances["market_session_id"].unique():
            session_data = self.performances[
                self.performances["market_session_id"] == session_id
            ]

            # Find best P&L for this session
            best_idx = session_data["profit_loss_percent"].idxmax()
            best_row = session_data.loc[best_idx]

            optimal_by_session.append(
                {
                    "market_session_id": session_id,
                    "optimal_rp_id": best_row["rp_id"],
                    "optimal_sp_id": best_row["sp_id"],
                    "optimal_trade_setup_id": best_row["trade_setup_id"],
                    "optimal_pl": best_row["profit_loss_percent"],
                }
            )

        optimal_df = pd.DataFrame(optimal_by_session)

        # Count frequency of each sp_id being optimal
        sp_id_counts = optimal_df["optimal_sp_id"].value_counts().sort_index()

        print("\nFrequency Each sp_id is Optimal:")
        print("-" * 40)
        total = len(optimal_df)
        for sp_id, count in sp_id_counts.items():
            pct = count / total * 100
            print(f"  sp_id={sp_id}: {count:4d} ({pct:5.1f}%)")

        # Compare sp_id=3 vs sp_id=4 specifically
        sp3_optimal = (optimal_df["optimal_sp_id"] == 3).sum()
        sp4_optimal = (optimal_df["optimal_sp_id"] == 4).sum()

        u.ascii.puts(f"\n📊 sp_id=3 vs sp_id=4 as Optimal Choice:", u.ascii.MAGENTA)
        print(f"  sp_id=3: {sp3_optimal} sessions ({sp3_optimal/total*100:.1f}%)")
        print(f"  sp_id=4: {sp4_optimal} sessions ({sp4_optimal/total*100:.1f}%)")
        print(
            f"  Ratio:   {sp3_optimal/sp4_optimal:.2f}:1"
            if sp4_optimal > 0
            else "  Ratio:   ∞:1"
        )

        return optimal_df, sp_id_counts

    def generate_recommendation(self, head_to_head_results, sp_id_counts):
        """Generate recommendation on whether to eliminate sp_id=4"""
        u.ascii.puts("\n" + "=" * 70, u.ascii.CYAN)
        u.ascii.puts("🎯 RECOMMENDATION", u.ascii.CYAN)
        u.ascii.puts("=" * 70, u.ascii.CYAN)

        # Calculate aggregate metrics
        total_sessions = head_to_head_results["sessions"].sum()
        weighted_sp3_win_rate = (
            head_to_head_results["sp3_wins"].sum() / total_sessions * 100
        )
        weighted_sp4_win_rate = (
            head_to_head_results["sp4_wins"].sum() / total_sessions * 100
        )

        avg_mean_diff = head_to_head_results["mean_diff"].mean()

        sp3_optimal_count = sp_id_counts.get(3, 0)
        sp4_optimal_count = sp_id_counts.get(4, 0)
        total_optimal = sp_id_counts.sum()

        sp3_optimal_pct = sp3_optimal_count / total_optimal * 100
        sp4_optimal_pct = sp4_optimal_count / total_optimal * 100

        print(f"\nAggregate Metrics:")
        print(f"  Head-to-Head Win Rate (sp_id=3): {weighted_sp3_win_rate:.1f}%")
        print(f"  Head-to-Head Win Rate (sp_id=4): {weighted_sp4_win_rate:.1f}%")
        print(f"  Average P&L Difference (sp3-sp4): {avg_mean_diff:+.2f}%")
        print(f"  Frequency as Optimal (sp_id=3):   {sp3_optimal_pct:.1f}%")
        print(f"  Frequency as Optimal (sp_id=4):   {sp4_optimal_pct:.1f}%")

        # Decision logic
        eliminate_sp4 = False
        reasons = []

        if weighted_sp3_win_rate >= 60:
            eliminate_sp4 = True
            reasons.append(
                f"sp_id=3 dominates head-to-head ({weighted_sp3_win_rate:.1f}% win rate)"
            )

        if sp4_optimal_pct < 20:
            eliminate_sp4 = True
            reasons.append(
                f"sp_id=4 rarely optimal ({sp4_optimal_pct:.1f}% of sessions)"
            )

        if avg_mean_diff > 5:
            eliminate_sp4 = True
            reasons.append(f"sp_id=3 has large P&L advantage (+{avg_mean_diff:.1f}%)")

        # Print recommendation
        print("\n" + "-" * 70)
        if eliminate_sp4:
            u.ascii.puts("✅ ELIMINATE sp_id=4", u.ascii.GREEN)
            print("\nReasons:")
            for reason in reasons:
                print(f"  • {reason}")
            print("\nBenefit: Reduce from 8 to 6 classes (~33% more samples per class)")
        else:
            u.ascii.puts("⚠️  KEEP sp_id=4", u.ascii.YELLOW)
            print("\nsp_id=4 shows competitive performance and should be retained.")
            print("Consider keeping both strategies in the multi-class model.")

        print("-" * 70)

        return eliminate_sp4, reasons

    def run_full_analysis(self):
        """Run complete analysis pipeline"""
        u.ascii.puts("\n" + "🔬 Starting Trade Setup Redundancy Analysis", u.ascii.CYAN)
        u.ascii.puts("=" * 70 + "\n", u.ascii.CYAN)

        # Step 1: Load all performances
        self.load_all_performances()

        # Step 2: Pivot data
        self.pivot_by_sp_id()

        # Step 3: Head-to-head analysis
        head_to_head_results = self.analyze_head_to_head()

        # Step 4: Optimal frequency analysis
        optimal_df, sp_id_counts = self.analyze_optimal_frequency()

        # Step 5: Generate recommendation
        eliminate, reasons = self.generate_recommendation(
            head_to_head_results, sp_id_counts
        )

        return {
            "performances": self.performances,
            "pivot_data": self.pivot_data,
            "head_to_head": head_to_head_results,
            "optimal_by_session": optimal_df,
            "sp_id_counts": sp_id_counts,
            "eliminate_sp4": eliminate,
            "reasons": reasons,
        }
