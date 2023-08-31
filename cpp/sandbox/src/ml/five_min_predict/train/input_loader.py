from math import floor
from ml.utils import ascii
import numpy as np


class InputLoader:
    BATCH_SIZE = 500

    def __init__(self, db_conn=None, symbol=""):
        self.db_conn = db_conn
        self.symbol = symbol

    def load(self):
        ascii.puts(f"💿 Loading input data for {ascii.CYAN}{self.symbol}", ascii.YELLOW)

        batches_n, rows = self.__get_batch_limted_candles()
        inputs = np.array(np.split(np.array(rows), batches_n, axis=0))

        return inputs

    def __get_batch_limted_candles(self):
        batches_n = self.__get_batches_n()

        with self.db_conn.conn.cursor() as cursor:
            query = """
                select
                  close,
                  high,
                  low,
                  open
                from
                  five_min_candles
                where
                  symbol = %(symbol)s
                order by
                  opened_at asc
                limit %(limit)s
            """

            cursor.execute(
                query,
                {
                    "limit": batches_n * InputLoader.BATCH_SIZE,
                    "symbol": self.symbol,
                },
            )

            rows = cursor.fetchall()

        return (batches_n, rows)

    def __get_batches_n(self):
        with self.db_conn.conn.cursor() as cursor:
            query = """
                select
                  count(*)
                from
                  five_min_candles
                where
                  symbol = %s
            """

            cursor.execute(query, [self.symbol])
            candles_count = cursor.fetchone()[0]

        return floor(candles_count / InputLoader.BATCH_SIZE)
