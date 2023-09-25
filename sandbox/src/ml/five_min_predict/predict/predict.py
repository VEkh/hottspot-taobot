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
        timestamps="now()",
    ):
        self.app_dir = os.environ.get("APP_DIR", ".")
        self.db_conn = db_conn
        self.input_loader = None
        self.model_names = ["convolutional", "linear", "lstm"]
        self.norm_factors = models.config.DEFAULT_NORM_FACTORS
        self.ref_epoch = ref_epoch
        self.symbol = symbol
        self.timestamps = timestamps

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

    def __log_prediction(
        self,
        _input={},
        model_name="",
        prediction={},
    ):
        u.ascii.puts(
            f"{model_name.upper()} {u.ascii.MAGENTA}PREDICTION",
            u.ascii.CYAN,
            u.ascii.UNDERLINE,
        )

        u.ascii.puts(
            f"Last Input: {json.dumps(_input, indent=2)}",
            u.ascii.YELLOW,
        )

        prediction_color = (
            u.ascii.RED if prediction["close"] < _input["close"] else u.ascii.GREEN
        )

        u.ascii.puts(
            f"Prediction: {json.dumps(prediction, indent=2)}",
            prediction_color,
        )

    def __predict_next(self):
        for model_name in self.model_names:
            predictions = self.models[model_name](self.input_loader.inputs_norm)

            self.predictions[model_name] = self.input_loader.postprocess(predictions)

            last_input_dict = self.input_loader.named_inputs[-1]

            last_prediction = self.predictions[model_name][-1, :].round(2).tolist()
            model = self.models[model_name]
            last_prediction_dict = dict(zip(model.label_columns, last_prediction))

            self.__log_prediction(
                _input=last_input_dict,
                model_name=model_name,
                prediction=last_prediction_dict,
            )

            self.__write_prediction(
                _input=last_input_dict,
                model_name=model_name,
                prediction=last_prediction_dict,
            )

    def __write_prediction(self, _input={}, model_name="", prediction={}):
        with self.db_conn.conn.cursor() as cursor:
            timestamp_val_format = (
                "%(timestamp)s"
                if self.timestamps == "now()"
                else "to_timestamp(%(timestamp)s)"
            )

            query = f"""
                insert into five_min_predictions(candle_closed_at, close, five_min_candle_id, high, low, model_name, open, symbol, updated_at)
                select
                  closed_at,
                  %(close)s,
                  %(five_min_candle_id)s,
                  %(high)s,
                  %(low)s,
                  %(model_name)s,
                  %(open)s,
                  %(symbol)s,
                  {timestamp_val_format}
                from
                  five_min_candles
                where
                  id = %(five_min_candle_id)s
                on conflict (five_min_candle_id,
                  model_name)
                  do update set close = excluded.close, high = excluded.high, low = excluded.low, open = excluded.open, updated_at = {timestamp_val_format}
            """

            cursor.execute(
                query,
                {
                    "close": prediction["close"],
                    "five_min_candle_id": _input["id"],
                    "high": prediction["high"],
                    "low": prediction["low"],
                    "model_name": model_name,
                    "open": prediction["open"],
                    "symbol": self.symbol,
                    "timestamp": self.timestamps,
                },
            )

            u.ascii.puts(cursor.statusmessage, u.ascii.CYAN)

        u.ascii.puts("💾 Wrote prediction to database.", u.ascii.GREEN)
