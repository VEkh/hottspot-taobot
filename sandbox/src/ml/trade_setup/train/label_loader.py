import ml.utils as u


class LabelLoader:
    def __init__(
        self,
        db_conn=None,
        market_session_duration_seconds=0,
        market_session_warm_up_duration_seconds=0,
        symbol=None,
    ):
        self.db_conn = db_conn
        self.labels = []
        self.market_session_duration_seconds = market_session_duration_seconds
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.symbol = symbol

    def load(self):

        self.__get_labels()

    def __get_labels(self):
        u.ascii.puts("💿 Loading labels", u.ascii.YELLOW)

        with self.db_conn.conn.cursor() as cursor:
            query = f"""
                with session_performances as (
                  select
                    market_sessions.open_period,
                    market_session_performances.market_session_id,
                    market_session_performances.profit_loss_percent,
                    market_session_performances.trade_setup_id,
                    row_number() over (partition by market_session_performances.market_session_id order by market_session_performances.profit_loss_percent desc,
                      trade_setups.priority asc) as rn
                  from
                    market_sessions
                    join market_session_performances on market_session_performances.market_session_id = market_sessions.id
                    join trade_setups on trade_setups.id = market_session_performances.trade_setup_id
                  where
                    market_sessions.symbol = %(symbol)s
                    and extract(epoch from upper(market_sessions.open_period) - lower(market_sessions.open_period)) =%(market_session_duration_seconds)s
                    and extract(epoch from upper(market_sessions.warm_up_period) - lower(market_sessions.warm_up_period)) =%(market_session_warm_up_duration_seconds)s)
                select
                  market_session_id,
                  trade_setup_id
                from
                  session_performances
                where
                  rn = 1
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

        self.labels = [dict(zip(columns, row)) for row in rows]

        u.ascii.puts("✅ Finished loading labels", u.ascii.YELLOW)
