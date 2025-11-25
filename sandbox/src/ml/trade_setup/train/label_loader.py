from tabulate import tabulate
import json
import ml.utils as u
import pandas as pd


class LabelLoader:
    def __init__(self, db_conn, market_session_ids=None):
        self.db_conn = db_conn
        self.labels = pd.DataFrame()
        self.market_session_ids = market_session_ids if market_session_ids else []

    def load(self):
        self._get_labels()
        self.labels = pd.DataFrame(self.labels)
        self._print_label_distribution()

        return self.labels

    def _get_labels(self):
        u.ascii.puts("💿 Loading labels", u.ascii.YELLOW)

        with self.db_conn.conn.cursor() as cursor:
            query = """
            with session_performances as (
              select
                market_sessions.open_period,
                market_session_performances.market_session_id,
                lower(market_sessions.open_period)::date as market_session_opened_at,
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
                and trade_setups.reverse_percentile_id in (1,2)
                and trade_setups.stop_profit_id in (1,2,3)
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

            cursor.execute(query, {"market_session_ids": self.market_session_ids})

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
