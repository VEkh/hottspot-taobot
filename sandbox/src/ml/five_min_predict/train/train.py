import json
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf

from ml.utils import ascii

from .baseline import Baseline
from .input_loader import InputLoader
from .window_generator import WindowGenerator


class Train:
    MAX_EPOCHS = 20

    def __init__(self, db_conn=None, env="", symbol=""):
        self.db_conn = db_conn
        self.env = env
        self.symbol = symbol
        self.test_performance = {}
        self.validation_performance = {}

        self.loader = InputLoader(db_conn=self.db_conn, symbol=self.symbol)

    def run(self):
        ascii.puts("🤖 Training five minute prediction model", ascii.YELLOW)

        self.loader.load()
        self.loader.preprocess()

        self.__train_baseline()
        self.__train_linear()
        self.__train_convolutional()
        self.__train_lstm()
        self.__log_performance()

    def __compile_and_fit(self, model=None, patience=2, window=None):
        early_stopping = tf.keras.callbacks.EarlyStopping(
            mode="min",
            monitor="val_loss",
            patience=patience,
        )

        model.compile(
            loss=tf.keras.losses.MeanSquaredError(),
            metrics=[tf.keras.metrics.MeanAbsoluteError()],
            optimizer=tf.keras.optimizers.Adam(),
        )

        history = model.fit(
            window.train,
            callbacks=[early_stopping],
            epochs=Train.MAX_EPOCHS,
            validation_data=window.validation,
        )

        return history

    def __evaluate(self, compiled_model=None, model_name="", window=None):
        ascii.puts("Evaluating Validation", end="")
        self.validation_performance[model_name] = compiled_model.evaluate(
            window.validation
        )

        ascii.puts("Evaluating Test", end="")
        self.test_performance[model_name] = compiled_model.evaluate(
            window.test, verbose=1
        )

    def __log_performance(self):
        ascii.puts("📈 PERFORMANCE", ascii.GREEN, ascii.UNDERLINE)
        ascii.puts(ascii.GREEN, begin="", end="", print_end="")
        print(
            "Validation: ",
            json.dumps(self.validation_performance, indent=2, sort_keys=True),
        )
        print(
            "Test:       ", json.dumps(self.test_performance, indent=2, sort_keys=True)
        )
        print(ascii.RESET, end="")

        self.__plot_performance()

    def __plot_performance(self):
        plt.figure(figsize=(12, 8))

        width = 0.3
        x = np.arange(len(self.test_performance))

        metric_name = "mean_absolute_error"
        metric_index = self.baseline_model.metrics_names.index("mean_absolute_error")

        test_y = [v[metric_index] for v in self.test_performance.values()]
        validation_y = [v[metric_index] for v in self.validation_performance.values()]

        plt.ylabel("mean_absolute_error [close, normalized]")
        plt.bar(x - 0.17, validation_y, width, label="Validation")
        plt.bar(x + 0.17, test_y, width, label="Test")
        plt.xticks(labels=self.test_performance.keys(), rotation=45, ticks=x)
        plt.legend()

        filepath = f"tmp/{self.symbol}_performance.png"
        plt.savefig(filepath)
        plt.clf()

        ascii.puts(f"📊 Performance plot saved to {ascii.CYAN}{filepath}", ascii.YELLOW)

    def __train_baseline(self):
        model_name = "baseline"

        window = WindowGenerator(
            input_columns=self.loader.columns,
            input_width=100,
            label_columns=["close"],
            label_width=1,
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

        model = Baseline(window=window)
        model.compile(
            loss=tf.keras.losses.MeanSquaredError(),
            metrics=[tf.keras.metrics.MeanAbsoluteError()],
        )

        self.__evaluate(compiled_model=model, model_name=model_name, window=window)

        print(ascii.RESET, end="")

        setattr(self, f"{model_name}_model", model)

        window.plot(
            filename=f"{self.symbol}_{model_name}.png",
            model=model,
            plot_column="close",
        )

    def __train_convolutional(self):
        conv_size = 3
        label_width = 100
        model_name = "convolutional"

        window = WindowGenerator(
            input_columns=self.loader.columns,
            input_width=label_width + (conv_size - 1),
            label_columns=["close"],
            label_width=label_width,
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

        model = tf.keras.Sequential(
            [
                tf.keras.layers.Conv1D(
                    activation="relu",
                    filters=32,
                    kernel_size=(conv_size,),
                ),
                tf.keras.layers.Dense(activation="relu", units=32),
                tf.keras.layers.Dense(units=1),
            ]
        )

        history = self.__compile_and_fit(model=model, window=window)

        self.__evaluate(compiled_model=model, model_name=model_name, window=window)

        print(ascii.RESET, end="")

        window.plot(
            filename=f"{self.symbol}_{model_name}.png",
            model=model,
            plot_column="close",
        )

    def __train_linear(self):
        model_name = "linear"

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

        model = tf.keras.Sequential([tf.keras.layers.Dense(units=1)])
        history = self.__compile_and_fit(model=model, window=window)

        self.__evaluate(compiled_model=model, model_name=model_name, window=window)

        print(ascii.RESET, end="")

        window.plot(
            filename=f"{self.symbol}_{model_name}.png",
            model=model,
            plot_column="close",
        )

    def __train_lstm(self):
        model_name = "lstm"

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

        model = tf.keras.Sequential(
            [
                tf.keras.layers.LSTM(return_sequences=True, units=32),
                tf.keras.layers.Dense(units=1),
            ]
        )
        history = self.__compile_and_fit(model=model, window=window)

        self.__evaluate(compiled_model=model, model_name=model_name, window=window)

        print(ascii.RESET, end="")

        window.plot(
            filename=f"{self.symbol}_{model_name}.png",
            model=model,
            plot_column="close",
        )
