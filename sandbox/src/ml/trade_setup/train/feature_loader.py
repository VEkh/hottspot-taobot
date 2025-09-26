import json
import ml.utils as u
import pandas as pd


class FeatureLoader:
    def __init__(
        self,
        db_conn=None,
        market_session_duration_seconds=0,
        market_session_warm_up_duration_seconds=0,
        symbol=None,
    ):
        self.columns = [
            "warm_up_body_to_lower_wick_ratio",
            "warm_up_body_to_range_ratio",
            "warm_up_body_to_upper_wick_ratio",
        ]

        self.db_conn = db_conn
        self.features = []
        self.market_session_duration_seconds = market_session_duration_seconds
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.symbol = symbol

    def load(self):
        self.__get_features()
        self.features = pd.DataFrame(self.features)

        return self.features

    def __get_features(self):
        u.ascii.puts("💿 Loading features", u.ascii.YELLOW)

        with self.db_conn.conn.cursor() as cursor:
            query = f"""
                select
                  id as market_session_id,
                  (abs(warm_up_close - warm_up_open) / abs(warm_up_high - warm_up_low)) as warm_up_body_to_range_ratio,
                  (abs(warm_up_close - warm_up_open) / abs(least(warm_up_close, warm_up_open) - warm_up_low)) as warm_up_body_to_lower_wick_ratio,
                  (abs(warm_up_close - warm_up_open) / abs(warm_up_high - greatest(warm_up_close, warm_up_open))) as warm_up_body_to_upper_wick_ratio,
                  (abs(warm_up_close - warm_up_open) / (abs(warm_up_high - warm_up_low) - abs(warm_up_close - warm_up_open))) as warm_up_body_to_wick_ratio
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

            self.features = [dict(zip(columns, row)) for row in rows]

            if not self.features:
                u.ascii.puts("🛑 No features loaded.", u.ascii.RED)
                return

            u.ascii.puts("✅ Finished loading features", u.ascii.YELLOW)
            u.ascii.puts(
                f"Example: {json.dumps(self.features[-1], indent=2)}", u.ascii.YELLOW
            )
