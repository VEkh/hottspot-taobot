import numpy as np
import tensorflow as tf

from ml.utils import ascii

from .input_loader import InputLoader
from .window_generator import WindowGenerator


class Train:
    def __init__(self, db_conn=None, env="", symbol=""):
        self.db_conn = db_conn
        self.env = env
        self.symbol = symbol

    def run(self):
        ascii.puts("🤖 Training five minute prediction model", ascii.YELLOW)

        loader = InputLoader(db_conn=self.db_conn, symbol=self.symbol)
        loader.load()
        loader.preprocess()

        window = WindowGenerator(
            input_columns=loader.columns,
            input_width=100,
            label_columns=["close"],
            label_width=1,
            shift=1,
            training_set=loader.training_set,
            test_set=loader.test_set,
            validation_set=loader.validation_set,
        )

        window.train
