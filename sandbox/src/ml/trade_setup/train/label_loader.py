from tabulate import tabulate
import json
import ml.utils as u
import pandas as pd


class LabelLoader:
    def __init__(
        self,
        db_conn=None,
        features=None,
    ):
        self.db_conn = db_conn
        self.features = features if features is not None else pd.DataFrame()
        self.labels = pd.DataFrame()

    def filter_sparse_classes(self, min_percentage=0.05):
        u.ascii.puts("💡 Filtering Sparse Label Classes", u.ascii.CYAN)

        u.ascii.puts("Original Class Distribution:", u.ascii.MAGENTA)
        self._print_label_distribution()

        target_column = "trade_setup_id"

        class_counts = self.labels[target_column].value_counts()
        total_count = len(self.labels)
        valid_classes = class_counts[
            (class_counts / total_count >= min_percentage)
        ].index

        removed_classes = set(class_counts.index) - set(valid_classes)

        u.ascii.puts(f"Removed Classes: {removed_classes}", u.ascii.MAGENTA)

        self.labels = self.labels[self.labels[target_column].isin(valid_classes)]

        u.ascii.puts("Filtered Class Distribution:", u.ascii.MAGENTA)
        self._print_label_distribution()

    def load(self):
        self._get_labels()
        self.labels = pd.DataFrame(self.labels)
        self._print_label_distribution()

        return self.labels

    def _get_labels(self):
        u.ascii.puts("💿 Loading labels", u.ascii.YELLOW)

        market_session_ids = (
            self.features["market_session_id"].to_numpy(dtype=int).tolist()
        )

        with self.db_conn.conn.cursor() as cursor:
            query = """
            with session_performances as (
              select
                market_sessions.open_period,
                market_session_performances.market_session_id,
                lower(market_sessions.open_period) as market_session_opened_at,
                market_session_performances.max_drawdown_percent,
                market_session_performances.profit_loss_percent,
                market_session_performances.time_to_max_drawdown_seconds,
                trade_setups.reverse_percentile_id,
                trade_setups.stop_profit_id,
                market_session_performances.trade_setup_id
              from
                market_sessions
                join market_session_performances on market_session_performances.market_session_id = market_sessions.id
                join trade_setups on trade_setups.id = market_session_performances.trade_setup_id
              where
                market_sessions.id = any(%(market_session_ids)s)
                and trade_setups.stop_profit_id not in (4)
            )
            select
              market_session_id,
              market_session_opened_at::text as market_session_opened_at,
              max_drawdown_percent,
              profit_loss_percent,
              reverse_percentile_id,
              stop_profit_id,
              time_to_max_drawdown_seconds,
              trade_setup_id
            from
              session_performances
            order by
              open_period asc
            """

            cursor.execute(
                query,
                {
                    "market_session_ids": market_session_ids,
                    "stop_profit_id": self.stop_profit_id,
                },
            )

            columns = [column.name for column in cursor.description]
            rows = cursor.fetchall()

        self.labels = [dict(zip(columns, row)) for row in rows]

        if not self.labels:
            u.ascii.puts("🛑 No labels loaded.", u.ascii.RED)
            return

        u.ascii.puts("✅ Finished loading labels", u.ascii.YELLOW)
        u.ascii.puts(
            f"Example: {json.dumps(self.labels[-1], indent=2)}", u.ascii.YELLOW
        )

    def _print_label_distribution(self):
        if self.labels.empty:
            return

        slice_keys = ["trade_setup_id", "reverse_percentile_id", "stop_profit_id"]

        grouped = (
            self.labels[slice_keys].groupby(slice_keys).size().reset_index(name="count")
        )

        grouped = grouped.sort_values("count", ascending=False)

        total_count = len(self.labels)

        grouped["percentage"] = (
            100.0 * (grouped["count"] / total_count) if total_count else 0
        )

        grouped["count"] = grouped.apply(
            lambda row: f"{row['count']} ({row['percentage']:.2f}%)", axis=1
        )

        grouped = grouped.drop("percentage", axis=1)

        table = grouped.to_dict("records")

        u.ascii.puts(tabulate(table, headers="keys", tablefmt="psql"), u.ascii.MAGENTA)
