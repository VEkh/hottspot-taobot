import json
import os
import tensorflow as tf
import time as t

from .input_loader import InputLoader
import ml.five_min_predict.models as models
import ml.utils as u


class Predict:
    def __init__(
        self,
        db_conn=None,
        ref_epoch=0,
        symbol="",
    ):
        self.app_dir = os.environ.get("APP_DIR", ".")
        self.db_conn = db_conn
        self.input_loader = None
        self.model_names = ["baseline", "convolutional", "linear", "lstm"]
        self.norm_factors = models.config.DEFAULT_NORM_FACTORS
        self.ref_epoch = ref_epoch
        self.symbol = symbol

        self.models = {k: None for k in self.model_names}
        self.predictions = {k: [] for k in self.model_names}

    def run(self):
        formatted_ref_epoch = t.strftime("%Y-%m-%d %X %Z", t.localtime(self.ref_epoch))

        start_prompt = u.string.strip_heredoc(
            f"""
            🤖 Predicting {u.ascii.CYAN}{self.symbol}'s{u.ascii.YELLOW}
            next five minute candle from: {u.ascii.CYAN}{formatted_ref_epoch}
            """
        )

        u.ascii.puts(start_prompt, u.ascii.YELLOW)

        self.__load_models()
        self.__load_inputs()
        self.__predict_next()

    def __load_inputs(self):
        self.input_loader = InputLoader(
            db_conn=self.db_conn,
            input_width=models.config.INPUT_WIDTH,
            norm_factors=self.norm_factors,
            ref_epoch=self.ref_epoch,
            symbol=self.symbol,
        )

        self.input_loader.load()
        self.input_loader.preprocess()

    def __load_models(self):
        data_dir = f"{self.app_dir}/data/ml/five_min_predict/models"

        for model_name in self.model_names:
            filepath = f"{data_dir}/{self.symbol}_{model_name}.keras"

            if os.path.isfile(filepath):
                model = tf.keras.models.load_model(filepath)
                self.models[model_name] = model

                self.norm_factors = model.norm_factors

                u.ascii.puts(
                    f"✅ Loaded trained model: {u.ascii.CYAN}{model_name}",
                    u.ascii.YELLOW,
                )

    def __log_prediction(self, model_name):
        last_input = self.input_loader.inputs[-1, :].tolist()
        last_prediction = self.predictions[model_name][-1, :].round(2).tolist()

        model = self.models[model_name]
        last_input_json = dict(zip(model.input_columns, last_input))
        last_prediction_json = dict(zip(model.label_columns, last_prediction))

        u.ascii.puts(
            f"{model_name.upper()} {u.ascii.MAGENTA}PREDICTION",
            u.ascii.CYAN,
            u.ascii.UNDERLINE,
        )
        u.ascii.puts(
            f"Last Input: {json.dumps(last_input_json, indent=2)}",
            u.ascii.YELLOW,
            begin="",
        )
        u.ascii.puts(
            f"Prediction: {json.dumps(last_prediction_json, indent=2)}",
            u.ascii.GREEN,
            begin="",
        )

    def __predict_next(self):
        for model_name in self.model_names:
            predictions = self.models[model_name](self.input_loader.inputs_norm)

            self.predictions[model_name] = self.input_loader.postprocess(predictions)

            self.__log_prediction(model_name)
