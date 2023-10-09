import json
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import os
import tensorflow as tf
import time

import ml.candle_predict.models as models
import ml.utils as u

from .input_loader import InputLoader
from .window_generator import WindowGenerator


class Train:
    MAX_EPOCHS = 20

    def __init__(self, db_conn=None, duration_minutes=5, symbol=None):
        self.app_dir = os.environ.get("APP_DIR", ".")
        self.db_conn = db_conn
        self.duration_minutes = duration_minutes
        self.input_width = models.config.INPUT_WIDTH
        self.label_columns = models.config.LABEL_COLUMNS
        self.ref_model = None
        self.start_epoch = time.time()
        self.symbol = symbol
        self.test_performance = {}
        self.validation_performance = {}

        self.input_loader = InputLoader(
            db_conn=self.db_conn,
            duration_minutes=self.duration_minutes,
            symbol=self.symbol,
        )

    def run(self):
        u.ascii.puts(
            f"🤖 Training {self.duration_minutes} minute prediction model",
            u.ascii.YELLOW,
        )

        self.input_loader.load()
        self.input_loader.preprocess()

        self.__train_baseline()
        self.__train_linear()
        self.__train_convolutional()
        self.__train_lstm()
        self.__log_performance()
        self.__log_duration()

    def __evaluate(self, model=None, window=None):
        u.ascii.puts("Evaluating Validation", end="")
        self.validation_performance[model.name] = model.evaluate(window.validation)

        u.ascii.puts("Evaluating Test", end="")
        self.test_performance[model.name] = model.evaluate(window.test, verbose=1)

    def __fit(self, model=None, patience=2, window=None):
        early_stopping = tf.keras.callbacks.EarlyStopping(
            mode="min",
            monitor="val_loss",
            patience=patience,
        )

        history = model.fit(
            window.train,
            callbacks=[early_stopping],
            epochs=Train.MAX_EPOCHS,
            validation_data=window.validation,
        )

        return history

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

    def __model_filename(self, model_name):
        return f"{self.__scope_filename()}{model_name}_{self.duration_minutes}min"

    def __persist_model(self, model):
        data_dir = f"{self.app_dir}/data/ml/candle_predict/models"
        os.makedirs(data_dir, exist_ok=True)

        filepath = f"{data_dir}/{self.__model_filename(model.name)}.keras"
        model.save(filepath=filepath, overwrite=True)

        u.ascii.puts(
            f"🧱 Persisted {u.ascii.CYAN}{model.name.upper()}{u.ascii.YELLOW} weights to {u.ascii.CYAN}{filepath}",
            u.ascii.YELLOW,
        )

    def __plot_performance(self):
        plt.figure(figsize=(12, 8))

        width = 0.3
        x = np.arange(len(self.test_performance))

        metric_name = "mean_absolute_error"
        metric_index = self.ref_model.metrics_names.index("mean_absolute_error")

        test_y = [v[metric_index] for v in self.test_performance.values()]
        validation_y = [v[metric_index] for v in self.validation_performance.values()]

        plt.ylabel("mean_absolute_error [close, normalized]")
        plt.bar(x - 0.17, validation_y, width, label="Validation")
        plt.bar(x + 0.17, test_y, width, label="Test")
        plt.xticks(labels=self.test_performance.keys(), rotation=45, ticks=x)
        plt.legend()

        filepath = f"{self.app_dir}/tmp/{self.__scope_filename()}{self.duration_minutes}min_performance.png"
        plt.savefig(filepath)
        plt.clf()

        u.ascii.puts(
            f"📊 Performance plot saved to {u.ascii.CYAN}{filepath}", u.ascii.YELLOW
        )

    def __plot_weights(self, model=None):
        columns_n = len(self.input_loader.columns)

        plt.figure(figsize=(12, 8))

        plt.bar(
            height=model.layers[0].kernel[:, 0].numpy(),
            x=range(columns_n),
        )

        axis = plt.gca()

        axis.set_xticks(range(columns_n))
        axis.set_xticklabels(self.input_loader.columns, rotation=90)

        savepath = f"{self.app_dir}/tmp/{self.__model_filename(model.name)}_weights.png"
        plt.savefig(savepath)
        plt.clf()

        u.ascii.puts(
            f"🧱📊 Weight plot saved to {u.ascii.CYAN}{savepath}", u.ascii.YELLOW
        )

    def __scope_filename(self):
        return f"{self.symbol}_" if self.symbol else ""

    def __train_baseline(self):
        columns = self.input_loader.columns

        window = WindowGenerator(
            input_columns=columns,
            input_width=self.input_width,
            label_columns=columns,
            label_width=self.input_width,
            shift=1,
            training_set=self.input_loader.training_set,
            test_set=self.input_loader.test_set,
            validation_set=self.input_loader.validation_set,
        )

        model = models.baseline.create(
            input_columns=window.input_columns,
            label_columns=window.label_columns,
            norm_factors=self.input_loader.norm_factors,
        )

        u.ascii.puts(
            f"🤖🔨 Training {u.ascii.CYAN}{model.name.upper()}\n",
            u.ascii.MAGENTA,
            u.ascii.UNDERLINE,
        )

        u.ascii.puts(u.ascii.MAGENTA, begin="", end="", print_end="")

        model.compile(
            loss=tf.keras.losses.MeanSquaredError(),
            metrics=[tf.keras.metrics.MeanAbsoluteError()],
        )

        self.__evaluate(model=model, window=window)

        print(u.ascii.RESET, end="")

        self.ref_model = model

        window.plot(
            filename=f"{self.__model_filename(model.name)}.png",
            model=model,
            plot_column="close",
        )

        self.__persist_model(model)

    def __train_convolutional(self):
        conv_size = models.config.CONVOLUTION_SIZE
        label_width = self.input_width

        window = WindowGenerator(
            input_columns=self.input_loader.columns,
            input_width=label_width + (conv_size - 1),
            label_columns=self.label_columns,
            label_width=label_width,
            shift=1,
            training_set=self.input_loader.training_set,
            test_set=self.input_loader.test_set,
            validation_set=self.input_loader.validation_set,
        )

        model = models.convolutional.create(
            input_columns=window.input_columns,
            label_columns=window.label_columns,
            norm_factors=self.input_loader.norm_factors,
        )

        u.ascii.puts(
            f"🤖🔨 Training {u.ascii.CYAN}{model.name.upper()}\n",
            u.ascii.MAGENTA,
            u.ascii.UNDERLINE,
        )

        u.ascii.puts(u.ascii.MAGENTA, begin="", end="", print_end="")

        self.__fit(model=model, window=window)
        self.__evaluate(model=model, window=window)

        print(u.ascii.RESET, end="")

        window.plot(
            filename=f"{self.__model_filename(model.name)}.png",
            model=model,
            plot_column="close",
        )

        self.__persist_model(model)

    def __train_linear(self):
        window = WindowGenerator(
            input_columns=self.input_loader.columns,
            input_width=self.input_width,
            label_columns=self.label_columns,
            label_width=self.input_width,
            shift=1,
            training_set=self.input_loader.training_set,
            test_set=self.input_loader.test_set,
            validation_set=self.input_loader.validation_set,
        )

        model = models.linear.create(
            input_columns=window.input_columns,
            label_columns=window.label_columns,
            norm_factors=self.input_loader.norm_factors,
        )

        u.ascii.puts(
            f"🤖🔨 Training {u.ascii.CYAN}{model.name.upper()}\n",
            u.ascii.MAGENTA,
            u.ascii.UNDERLINE,
        )

        u.ascii.puts(u.ascii.MAGENTA, begin="", end="", print_end="")

        self.__fit(model=model, window=window)
        self.__evaluate(model=model, window=window)
        self.__plot_weights(model)

        print(u.ascii.RESET, end="")

        window.plot(
            filename=f"{self.__model_filename(model.name)}.png",
            model=model,
            plot_column="close",
        )

        self.__persist_model(model)

    def __train_lstm(self):
        window = WindowGenerator(
            input_columns=self.input_loader.columns,
            input_width=self.input_width,
            label_columns=self.label_columns,
            label_width=self.input_width,
            shift=1,
            training_set=self.input_loader.training_set,
            test_set=self.input_loader.test_set,
            validation_set=self.input_loader.validation_set,
        )

        model = models.lstm.create(
            input_columns=window.input_columns,
            label_columns=window.label_columns,
            norm_factors=self.input_loader.norm_factors,
        )

        u.ascii.puts(
            f"🤖🔨 Training {u.ascii.CYAN}{model.name.upper()}\n",
            u.ascii.MAGENTA,
            u.ascii.UNDERLINE,
        )

        u.ascii.puts(u.ascii.MAGENTA, begin="", end="", print_end="")

        self.__fit(model=model, window=window)
        self.__evaluate(model=model, window=window)

        print(u.ascii.RESET, end="")

        window.plot(
            filename=f"{self.__model_filename(model.name)}.png",
            model=model,
            plot_column="close",
        )

        self.__persist_model(model)
