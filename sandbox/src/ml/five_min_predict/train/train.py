import json
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
import time

import ml.utils as u

from .baseline import Baseline
from .input_loader import InputLoader
from .window_generator import WindowGenerator


class Train:
    MAX_EPOCHS = 20

    def __init__(self, db_conn=None, env="", symbol=""):
        self.db_conn = db_conn
        self.env = env
        self.label_columns = [
            "close",
            "high",
            "low",
            "open",
        ]
        self.start_epoch = time.time()
        self.symbol = symbol
        self.test_performance = {}
        self.validation_performance = {}

        self.loader = InputLoader(db_conn=self.db_conn, symbol=self.symbol)

    def run(self):
        u.ascii.puts("🤖 Training five minute prediction model", u.ascii.YELLOW)

        self.loader.load()
        self.loader.preprocess()

        input_width = 150
        self.__train_baseline(input_width)
        self.__train_linear(input_width)
        self.__train_convolutional(input_width)
        self.__train_lstm(input_width)
        self.__log_performance()
        self.__log_duration()

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
        u.ascii.puts("Evaluating Validation", end="")
        self.validation_performance[model_name] = compiled_model.evaluate(
            window.validation
        )

        u.ascii.puts("Evaluating Test", end="")
        self.test_performance[model_name] = compiled_model.evaluate(
            window.test, verbose=1
        )

    def __log_duration(self):
        duration = round(time.time() - self.start_epoch, 3)

        u.ascii.puts(
            f"⌚ Finished in {u.ascii.CYAN}{u.time.seconds_to_clock(duration)}",
            u.ascii.YELLOW,
        )

    def __log_performance(self):
        u.ascii.puts("📈 PERFORMANCE", u.ascii.GREEN, u.ascii.UNDERLINE)
        u.ascii.puts(u.ascii.GREEN, begin="", end="", print_end="")
        print(
            "Validation: ",
            json.dumps(self.validation_performance, indent=2, sort_keys=True),
        )
        print(
            "Test:       ", json.dumps(self.test_performance, indent=2, sort_keys=True)
        )
        print(u.ascii.RESET, end="")

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

        u.ascii.puts(
            f"📊 Performance plot saved to {u.ascii.CYAN}{filepath}", u.ascii.YELLOW
        )

    def __train_baseline(self, input_width):
        model_name = "baseline"

        columns = self.loader.columns

        window = WindowGenerator(
            input_columns=columns,
            input_width=input_width,
            label_columns=columns,
            label_width=input_width,
            shift=1,
            training_set=self.loader.training_set,
            test_set=self.loader.test_set,
            validation_set=self.loader.validation_set,
        )

        u.ascii.puts(
            f"🤖🔨 Training {u.ascii.CYAN}{model_name.upper()}\n",
            u.ascii.MAGENTA,
            u.ascii.UNDERLINE,
        )

        u.ascii.puts(u.ascii.MAGENTA, begin="", end="", print_end="")

        model = Baseline(window=window)
        model.compile(
            loss=tf.keras.losses.MeanSquaredError(),
            metrics=[tf.keras.metrics.MeanAbsoluteError()],
        )

        self.__evaluate(compiled_model=model, model_name=model_name, window=window)

        print(u.ascii.RESET, end="")

        setattr(self, f"{model_name}_model", model)

        window.plot(
            filename=f"{self.symbol}_{model_name}.png",
            model=model,
            plot_column="close",
        )

    def __train_convolutional(self, input_width):
        conv_size = 3
        label_width = input_width
        model_name = "convolutional"

        window = WindowGenerator(
            input_columns=self.loader.columns,
            input_width=label_width + (conv_size - 1),
            label_columns=self.label_columns,
            label_width=label_width,
            shift=1,
            training_set=self.loader.training_set,
            test_set=self.loader.test_set,
            validation_set=self.loader.validation_set,
        )

        u.ascii.puts(
            f"🤖🔨 Training {u.ascii.CYAN}{model_name.upper()}\n",
            u.ascii.MAGENTA,
            u.ascii.UNDERLINE,
        )

        u.ascii.puts(u.ascii.MAGENTA, begin="", end="", print_end="")

        model = tf.keras.Sequential(
            [
                tf.keras.layers.Conv1D(
                    activation="relu",
                    filters=32,
                    kernel_size=(conv_size,),
                ),
                tf.keras.layers.Dense(activation="relu", units=32),
                tf.keras.layers.Dense(units=len(self.label_columns)),
            ]
        )

        history = self.__compile_and_fit(model=model, window=window)

        self.__evaluate(compiled_model=model, model_name=model_name, window=window)

        print(u.ascii.RESET, end="")

        window.plot(
            filename=f"{self.symbol}_{model_name}.png",
            model=model,
            plot_column="close",
        )

    def __train_linear(self, input_width):
        model_name = "linear"

        window = WindowGenerator(
            input_columns=self.loader.columns,
            input_width=input_width,
            label_columns=self.label_columns,
            label_width=input_width,
            shift=1,
            training_set=self.loader.training_set,
            test_set=self.loader.test_set,
            validation_set=self.loader.validation_set,
        )

        u.ascii.puts(
            f"🤖🔨 Training {u.ascii.CYAN}{model_name.upper()}\n",
            u.ascii.MAGENTA,
            u.ascii.UNDERLINE,
        )

        u.ascii.puts(u.ascii.MAGENTA, begin="", end="", print_end="")

        model = tf.keras.Sequential(
            [tf.keras.layers.Dense(units=len(self.label_columns))]
        )
        history = self.__compile_and_fit(model=model, window=window)

        self.__evaluate(compiled_model=model, model_name=model_name, window=window)

        print(u.ascii.RESET, end="")

        window.plot(
            filename=f"{self.symbol}_{model_name}.png",
            model=model,
            plot_column="close",
        )

    def __train_lstm(self, input_width):
        model_name = f"lstm-{input_width}"

        window = WindowGenerator(
            input_columns=self.loader.columns,
            input_width=input_width,
            label_columns=self.label_columns,
            label_width=input_width,
            shift=1,
            training_set=self.loader.training_set,
            test_set=self.loader.test_set,
            validation_set=self.loader.validation_set,
        )

        u.ascii.puts(
            f"🤖🔨 Training {u.ascii.CYAN}{model_name.upper()}\n",
            u.ascii.MAGENTA,
            u.ascii.UNDERLINE,
        )

        u.ascii.puts(u.ascii.MAGENTA, begin="", end="", print_end="")

        model = tf.keras.Sequential(
            [
                tf.keras.layers.LSTM(return_sequences=True, units=32),
                tf.keras.layers.Dense(
                    kernel_initializer=tf.initializers.zeros(),
                    units=len(self.label_columns),
                ),
            ]
        )
        history = self.__compile_and_fit(model=model, window=window)

        self.__evaluate(compiled_model=model, model_name=model_name, window=window)

        print(u.ascii.RESET, end="")

        window.plot(
            filename=f"{self.symbol}_{model_name}.png",
            model=model,
            plot_column="close",
        )
