from math import floor
import numpy as np

import ml.candle_predict.models as models
import ml.utils as u


class InputLoader:
    def __init__(self, db_conn=None, duration_minutes=0, symbol=None):
        self.db_conn = db_conn
        self.duration_minutes = duration_minutes
        self.columns = []
        self.inputs = np.array([])
        self.norm_factors = models.config.DEFAULT_NORM_FACTORS
        self.selected_input_columns = ",\n".join(models.config.SELECTED_INPUT_COLUMNS)
        self.symbol = symbol
        self.test_set = np.array([])
        self.training_set = np.array([])
        self.validation_set = np.array([])

    def load(self):
        if self.symbol:
            self.__get_inputs_for_symbol()
        else:
            self.__get_inputs_for_all()

    def preprocess(self):
        self.__split_into_sets()
        self.__normalize()

    def __get_inputs_for_all(self):
        u.ascii.puts(
            f"💿 Loading input data for {u.ascii.CYAN}all symbols", u.ascii.YELLOW
        )

        with self.db_conn.conn.cursor() as cursor:
            query = f"""
                select
                  candles.*
                from (
                  select
                    symbol,
                    (count(*) / %(input_width)s) as multiplier
                  from
                    candles
                  where
                    duration_minutes = %(duration_minutes)s
                  group by
                    symbol
                  order by
                    symbol asc) as symbols
                  join lateral (
                    select
                      {self.selected_input_columns},
                      symbol
                    from
                      candles
                    where
                      symbol = symbols.symbol
                      and duration_minutes = %(duration_minutes)s
                    order by
                      opened_at asc
                    limit (symbols.multiplier * %(input_width)s)) as candles on candles.symbol = symbols.symbol;
            """

            cursor.execute(
                query,
                {
                    "duration_minutes": self.duration_minutes,
                    "input_width": models.config.INPUT_WIDTH,
                },
            )

            columns = [column.name for column in cursor.description]
            rows = cursor.fetchall()

        n = len(models.config.SELECTED_INPUT_COLUMNS)

        self.columns = columns[:n]
        self.inputs = np.array(rows)[:, :n].astype(float)

        u.ascii.puts(f"✅ Fetched candles. Shape: {self.inputs.shape}", u.ascii.GREEN)

    def __get_inputs_for_symbol(self):
        u.ascii.puts(
            f"💿 Loading input data for {u.ascii.CYAN}{self.symbol}", u.ascii.YELLOW
        )

        with self.db_conn.conn.cursor() as cursor:
            query = f"""
                select
                  {self.selected_input_columns}
                from
                  candles
                where
                  symbol = %(symbol)s
                  and duration_minutes = %(duration_minutes)s
                order by
                  opened_at asc
            """

            cursor.execute(
                query,
                {
                    "duration_minutes": self.duration_minutes,
                    "symbol": self.symbol,
                },
            )

            columns = [column.name for column in cursor.description]
            rows = cursor.fetchall()

        self.columns = columns
        self.inputs = np.array(rows)

        u.ascii.puts(f"✅ Fetched candles. Shape: {self.inputs.shape}", u.ascii.GREEN)

    def __normalize(self):
        training_set_mean = self.training_set.mean(axis=0)
        training_set_std = self.training_set.std(axis=0)

        self.norm_factors = {
            "mean": training_set_mean,
            "std": training_set_std,
        }

        self.test_set = (self.test_set - training_set_mean) / training_set_std
        self.training_set = (self.training_set - training_set_mean) / training_set_std
        self.validation_set = (
            self.validation_set - training_set_mean
        ) / training_set_std

        u.ascii.puts(f"✅ Normalized data sets.", u.ascii.GREEN)

    def __shuffle_rows(self, features_n=0, rows=[]):
        input_width = models.config.INPUT_WIDTH
        m = len(rows)
        n = features_n

        groups_n = int(m / input_width)

        grouped_rows = (
            np.array(rows)[:, :n].astype(float).reshape(groups_n, input_width, n)
        )

        idx = np.arange(grouped_rows.shape[0])
        np.random.shuffle(idx)

        shuffled_rows = grouped_rows[idx, :]

        return shuffled_rows.reshape(m, n)

    def __split_into_sets(self):
        m = len(self.inputs)

        self.test_set = self.inputs[int(m * 0.9) :]
        self.training_set = self.inputs[0 : int(m * 0.7)]
        self.validation_set = self.inputs[int(m * 0.7) : int(m * 0.9)]

        u.ascii.puts(u.ascii.MAGENTA, begin="", end="")
        u.ascii.puts(
            "📝 DATA SET SIZES:",
            u.ascii.UNDERLINE,
            begin="",
            end=u.ascii.NO_UNDERLINE,
        )
        print(f"Training:   {len(self.training_set)}")
        print(f"Validation: {len(self.validation_set)}")
        print(f"Test:       {len(self.test_set)}")
        print(f"Total:      {m}")
        print(u.ascii.RESET, end="")
