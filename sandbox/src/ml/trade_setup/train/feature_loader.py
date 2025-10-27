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
        self.candle_feature_columns = [
            "warm_up_body_to_lower_wick_ratio",
            "warm_up_body_to_upper_wick_ratio",
            "warm_up_body_to_wick_ratio",
        ]

        self.market_regime_feature_colums = [
            "avg_true_range_26",
        ]

        self.columns = self.candle_feature_columns

        self.candle_features = []
        self.db_conn = db_conn
        self.features = pd.DataFrame()
        self.market_regime_features = []
        self.market_session_duration_seconds = market_session_duration_seconds
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.symbol = symbol

    def load(self):
        self._get_candle_features()
        self._get_market_regime_features()

        self.features = pd.merge(
            pd.DataFrame(self.candle_features),
            pd.DataFrame(self.market_regime_features),
            how="inner",
            on="market_session_id",
        )

        self._cap_outliers()

        return self.features

    def _cap_outliers(self):
        for column in self.candle_feature_columns:
            cap = self.features[column].quantile(0.99)
            self.features[column] = self.features[column].clip(upper=cap)

    def _get_candle_features(self):
        u.ascii.puts("💿 Loading candle features", u.ascii.YELLOW)

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

            self.candle_features = [dict(zip(columns, row)) for row in rows]

            if not self.candle_features:
                u.ascii.puts("🛑 No candle features loaded.", u.ascii.RED)
                return

            u.ascii.puts("✅ Finished loading candle features", u.ascii.YELLOW)
            u.ascii.puts(
                f"Example: {json.dumps(self.candle_features[-1], indent=2)}",
                u.ascii.YELLOW,
            )

    def _get_market_regime_features(self):
        u.ascii.puts("💿 Loading regime features", u.ascii.YELLOW)

        with self.db_conn.conn.cursor() as cursor:
            query = f"""
                with with_previous_close as (
                  select
                    id as market_session_id,
                    open_period,
                    high,
                    low,
                    lag(close) over (order by open_period asc) as previous_close,
                    (high - low) as range
                  from
                    market_sessions
                  where
                    symbol = %(symbol)s
                    and extract(epoch from upper(open_period) - lower(open_period)) = %(market_session_duration_seconds)s
                    and extract(epoch from upper(warm_up_period) - lower(warm_up_period)) = %(market_session_warm_up_duration_seconds)s
                ),
                with_true_ranges as (
                  select
                    market_sessions.id as market_session_id,
                    market_sessions.open_period,
                    greatest(
                        with_previous_close.range,
                        abs(with_previous_close.high - with_previous_close.previous_close),
                        abs(with_previous_close.low - with_previous_close.previous_close)
                    ) as true_range
                  from
                    market_sessions
                    join with_previous_close on with_previous_close.market_session_id = market_sessions.id
                  where
                    with_previous_close.previous_close is not null
                    and with_previous_close.range > 0.0
                ),
                with_avg_true_ranges_calc as (
                  select
                    *,
                    count(*) over (
                        order by open_period asc
                        rows between 26 preceding and 1 preceding
                    ) as session_count,
                    avg(true_range) over (
                        order by open_period asc
                        rows between 26 preceding and 1 preceding
                    ) as avg_true_range_26_raw
                  from
                    with_true_ranges
                )
                select
                  market_session_id,
                  avg_true_range_26_raw as avg_true_range_26
                from
                  with_avg_true_ranges_calc
                where
                  session_count = 26
                order by
                  open_period desc
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

            self.market_regime_features = [dict(zip(columns, row)) for row in rows]

            if not self.market_regime_features:
                u.ascii.puts("🛑 No market regime features loaded.", u.ascii.RED)
                return

            u.ascii.puts("✅ Finished loading market regime features", u.ascii.YELLOW)
            u.ascii.puts(
                f"Example: {json.dumps(self.market_regime_features[-1], indent=2)}",
                u.ascii.YELLOW,
            )
