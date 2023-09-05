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

        candles = self.__get_candles()
        inputs = np.array(candles)

        return inputs

    def __get_candles(self):
        with self.db_conn.conn.cursor() as cursor:
            query = """
                select
                  close,
                  high,
                  low,
                  open,
                  cos((extract(epoch from opened_at) * pi()) /(24 * 60 * 60)) as opened_at_day_cos,
                  sin((extract(epoch from opened_at) * pi()) /(24 * 60 * 60)) as opened_at_day_sin
                from
                  five_min_candles
                where
                  symbol = %(symbol)s
                order by
                  opened_at asc
            """

            cursor.execute(query, {"symbol": self.symbol})

            rows = cursor.fetchall()

        return rows
