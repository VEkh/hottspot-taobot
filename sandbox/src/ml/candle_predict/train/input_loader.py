from math import floor
import numpy as np

import ml.candle_predict.models as models
import ml.utils as u


class InputLoader:
    def __init__(self, db_conn=None, duration_minutes=0, symbol=None):
        self.db_conn = db_conn
        self.duration_minutes = duration_minutes
        self.columns = []
        self.inputs = {}
        self.norm_factors = models.config.DEFAULT_NORM_FACTORS
        self.selected_input_columns = ",\n".join(models.config.SELECTED_INPUT_COLUMNS)
        self.symbol = symbol
        self.test_set = np.array([])
        self.training_set = np.array([])
        self.validation_set = np.array([])

    def load(self):
        if self.symbol:
            self.__get_inputs_for_symbol(self.symbol)
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
                  symbol,
                  (count(*) / %(input_width)s) as multiplier
                from
                  candles
                where
                  duration_minutes = %(duration_minutes)s
                group by
                  symbol
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

        for symbol, multiplier in rows:
            self.__get_inputs_for_symbol(
                limit=multiplier * models.config.INPUT_WIDTH, symbol=symbol
            )

        u.ascii.puts(f"✅ Fetched candles for all symbols", u.ascii.GREEN)

    def __get_inputs_for_symbol(self, limit=0, symbol=""):
        u.ascii.puts(f"💿 Loading input data for {u.ascii.CYAN}{symbol}", u.ascii.YELLOW)

        with self.db_conn.conn.cursor() as cursor:
            limit_clause = f"limit %(limit)s" if limit else ""

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
                {limit_clause}
            """

            cursor.execute(
                query,
                {
                    "duration_minutes": self.duration_minutes,
                    "limit": limit,
                    "symbol": symbol,
                },
            )

            columns = [column.name for column in cursor.description]
            rows = cursor.fetchall()

        self.columns = columns
        self.inputs[symbol] = [list(r) for r in rows]

        u.ascii.puts(
            f"✅ Fetched candles. Shape: {np.array(self.inputs[symbol]).shape}",
            u.ascii.GREEN,
        )

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

    def __split_into_sets(self):
        M = 0
        test_set = []
        training_set = []
        validation_set = []

        for key, inputs in self.inputs.items():
            m = len(inputs)
            M += m

            training_set += inputs[0 : int(m * 0.7)]
            validation_set += inputs[int(m * 0.7) : int(m * 0.9)]
            test_set += inputs[int(m * 0.9) :]

        self.test_set = np.array(test_set)
        self.training_set = np.array(training_set)
        self.validation_set = np.array(validation_set)

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
        print(f"Total:      {M}")
        print(u.ascii.RESET, end="")
