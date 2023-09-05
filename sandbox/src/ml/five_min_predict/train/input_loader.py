from math import floor
from ml.utils import ascii
import numpy as np


class InputLoader:
    def __init__(self, db_conn=None, symbol=""):
        self.db_conn = db_conn
        self.columns = []
        self.inputs = np.array([])
        self.symbol = symbol
        self.test_set = np.array([])
        self.training_set = np.array([])
        self.validation_set = np.array([])

    def load(self):
        ascii.puts(
            f"\n💿 Loading input data for {ascii.CYAN}{self.symbol}", ascii.YELLOW
        )

        self.__get_from_db()

    def preprocess(self):
        self.__split_into_sets()
        self.__normalize()

    def __get_from_db(self):
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

            columns = [column.name for column in cursor.description]
            rows = cursor.fetchall()

        self.columns = columns
        self.inputs = np.array(rows)

        ascii.puts(f"\n✅ Fetched candles. Shape: {self.inputs.shape}", ascii.GREEN)

    def __normalize(self):
        training_set_mean = self.training_set.mean(axis=0)
        training_set_std = self.training_set.std(axis=0)

        self.test_set = (self.test_set - training_set_mean) / training_set_std
        self.training_set = (self.training_set - training_set_mean) / training_set_std
        self.validation_set = (
            self.validation_set - training_set_mean
        ) / training_set_std

        ascii.puts(f"\n✅ Normalized data sets.", ascii.GREEN)

    def __split_into_sets(self):
        n = len(self.inputs)

        self.test_set = self.inputs[int(n * 0.9) :]
        self.training_set = self.inputs[0 : int(n * 0.7)]
        self.validation_set = self.inputs[int(n * 0.7) : int(n * 0.9)]

        ascii.puts("\n📝 Data Set Sizes:".upper(), ascii.MAGENTA, ascii.UNDERLINE)
        print(f"{ascii.BOLD}{ascii.MAGENTA}", end="")
        print(f"Training:   {len(self.training_set)}")
        print(f"Validation: {len(self.validation_set)}")
        print(f"Test:       {len(self.test_set)}")
        print(f"Total:      {n}")
        print(f"{ascii.RESET}", end="")
