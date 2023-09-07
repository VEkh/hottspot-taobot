import numpy as np
import tensorflow as tf

from ml.utils import ascii

from .baseline import Baseline
from .input_loader import InputLoader
from .window_generator import WindowGenerator


class Train:
    def __init__(self, db_conn=None, env="", symbol=""):
        self.db_conn = db_conn
        self.env = env
        self.performance = {}
        self.symbol = symbol
        self.validation_performance = {}

        self.loader = InputLoader(db_conn=self.db_conn, symbol=self.symbol)

    def run(self):
        ascii.puts("🤖 Training five minute prediction model", ascii.YELLOW)

        self.loader.load()
        self.loader.preprocess()

        self.__train_baseline()
        self.__print_performance()

    def __print_performance(self):
        ascii.puts("📈 PERFORMANCE", ascii.GREEN, ascii.UNDERLINE)
        ascii.puts(ascii.GREEN, begin="", end="", print_end="")
        print("Validation: ", self.validation_performance)
        print("Test:       ", self.performance)
        print(ascii.RESET, end="")

    def __train_baseline(self):
        model_name = "baseline"

        window = WindowGenerator(
            input_columns=self.loader.columns,
            input_width=100,
            label_columns=["close"],
            label_width=100,
            shift=1,
            training_set=self.loader.training_set,
            test_set=self.loader.test_set,
            validation_set=self.loader.validation_set,
        )

        ascii.puts(
            f"🤖🔨 Training {ascii.CYAN}{model_name.upper()}\n",
            ascii.MAGENTA,
            ascii.UNDERLINE,
        )

        ascii.puts(ascii.MAGENTA, begin="", end="", print_end="")
        model = Baseline(label_index=window.column_indices["close"])
        model.compile(
            loss=tf.keras.losses.MeanSquaredError(),
            metrics=[tf.keras.metrics.MeanAbsoluteError()],
        )

        ascii.puts("Evaluating Validation:", end="")
        self.validation_performance[model_name] = model.evaluate(window.validation)

        ascii.puts("Evaluating Test:", end="")
        self.performance[model_name] = model.evaluate(window.test, verbose=1)
        print(ascii.RESET, end="")

        window.plot(filename=f"{model_name}.png", model=model, plot_column="close")
