import json
import ml.utils as u


class InputLoader:
    def __init__(
        self,
        db_conn=None,
        market_session_duration_seconds=0,
        market_session_warm_up_duration_seconds=0,
        symbol=None,
    ):
        self.db_conn = db_conn
        self.inputs = []
        self.market_session_duration_seconds = market_session_duration_seconds
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.symbol = symbol

    def load(self):
        self.__get_inputs()

    def __get_inputs(self):
        u.ascii.puts("💿 Loading inpus", u.ascii.YELLOW)

        with self.db_conn.conn.cursor() as cursor:
            query = f"""
                select
                  id as market_session_id,
                  (abs(warm_up_close - warm_up_open) / abs(warm_up_high - warm_up_low)) as warm_up_body_to_range_ratio,
                  (abs(warm_up_close - warm_up_open) / abs(least(warm_up_close, warm_up_open) - warm_up_low)) as warm_up_body_to_lower_wick_ratio,
                  (abs(warm_up_close - warm_up_open) / abs(warm_up_high - greatest(warm_up_close, warm_up_open))) as warm_up_body_to_upper_wick_ratio
                from
                  market_sessions
                where
                  symbol = %(symbol)s
                  and extract(epoch from upper(open_period) - lower(open_period)) = %(market_session_duration_seconds)s
                  and extract(epoch from upper(warm_up_period) - lower(warm_up_period)) = %(market_session_warm_up_duration_seconds)s
                  and abs(warm_up_high - warm_up_low) != 0.0
                  and abs(least(warm_up_close, warm_up_open) - warm_up_low) != 0.0
                  and abs(warm_up_high - greatest(warm_up_close, warm_up_open)) != 0.0
                order by
                  open_period asc
            """

            cursor.execute(
                query,
                {
                    "market_session_duration_seconds": self.market_session_duration_seconds,
                    "market_session_warm_up_duration_seconds": self.market_session_warm_up_duration_seconds,
                    "symbol": self.symbol,
                },
            )

            columns = [column.name for column in cursor.description]
            rows = cursor.fetchall()

            self.inputs = [dict(zip(columns, row)) for row in rows]

            u.ascii.puts("✅ Finished loading inputs", u.ascii.YELLOW)
            u.ascii.puts(
                f"Example: {json.dumps(self.inputs[-1], indent=2)}", u.ascii.YELLOW
            )
