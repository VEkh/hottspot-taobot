from tabulate import tabulate
import json
import ml.utils as u


class LabelLoader:
    def __init__(
        self,
        db_conn=None,
        inputs=[],
    ):
        self.db_conn = db_conn
        self.inputs = inputs
        self.labels = []

    def load(self):
        self.__get_labels()
        self.__print_label_grouping()

        return self.labels

    def __get_labels(self):
        u.ascii.puts("💿 Loading labels", u.ascii.YELLOW)

        market_session_ids = [row["market_session_id"] for row in self.inputs]

        with self.db_conn.conn.cursor() as cursor:
            query = """
                with session_performances as (
                  select
                    market_sessions.open_period,
                    market_session_performances.market_session_id,
                    market_session_performances.profit_loss_percent,
                    trade_setups.reverse_percentile_id,
                    trade_setups.stop_profit_id,
                    market_session_performances.trade_setup_id,
                    row_number() over (partition by market_session_performances.market_session_id order by market_session_performances.profit_loss_percent desc,
                      trade_setups.priority asc) as rn
                  from
                    market_sessions
                    join market_session_performances on market_session_performances.market_session_id = market_sessions.id
                    join trade_setups on trade_setups.id = market_session_performances.trade_setup_id
                  where
                    market_sessions.id = any(%(market_session_ids)s)
                )
                select
                  market_session_id,
                  reverse_percentile_id,
                  stop_profit_id,
                  trade_setup_id
                from
                  session_performances
                where
                  rn = 1
                order by
                  open_period asc
            """

            cursor.execute(query, {"market_session_ids": market_session_ids})

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

    def __print_label_grouping(self):
        if not self.labels:
            return

        groupings = {}

        for label in self.labels:
            slice_keys = ["trade_setup_id", "reverse_percentile_id", "stop_profit_id"]

            group = groupings.get(label["trade_setup_id"]) or (
                {k: label[k] for k in slice_keys} | {"count": 0}
            )

            group["count"] = group["count"] + 1

            groupings[label["trade_setup_id"]] = group

        table = [groupings[k] for k in groupings]
        table = sorted(table, key=lambda i: i["count"], reverse=True)

        u.ascii.puts("Label Counts:", u.ascii.YELLOW)
        u.ascii.puts(tabulate(table, headers="keys", tablefmt="psql"), u.ascii.YELLOW)
