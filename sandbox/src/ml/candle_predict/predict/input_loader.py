import numpy as np
import tensorflow as tf
import sys

import ml.candle_predict.models as models
import ml.utils as u


class InputLoader:
    def __init__(
        self,
        db_conn=None,
        duration_minutes=0,
        input_width=0,
        norm_factors=models.config.DEFAULT_NORM_FACTORS,
        ref_epoch=0,
        symbol="",
    ):
        self.db_conn = db_conn
        self.duration_minutes = duration_minutes
        self.input_width = input_width
        self.inputs = np.array([])
        self.inputs_norm = np.array([])
        self.named_inputs = []
        self.norm_factors = norm_factors
        self.ref_epoch = ref_epoch
        self.symbol = symbol

    def load(self):
        u.ascii.puts(
            f"💿 Loading input data for {u.ascii.CYAN}{self.symbol}", u.ascii.YELLOW
        )

        self.__get_inputs_from_db()

    def postprocess(self, out):
        outputs = np.squeeze(out.numpy(), axis=0)

        return self.__denormalize(outputs)

    def preprocess(self):
        self.__normalize()
        self.inputs_norm = tf.reshape(self.inputs_norm, (1,) + self.inputs_norm.shape)

    def __denormalize(self, normalized):
        features_n = normalized.shape[1]

        truncated_norm_factors = {
            k: v[:, :features_n] for k, v in self.norm_factors.items()
        }

        return (normalized * truncated_norm_factors["std"]) + truncated_norm_factors[
            "mean"
        ]

    def __get_inputs_from_db(self):
        selected_input_columns = ",\n".join(models.config.SELECTED_INPUT_COLUMNS)

        with self.db_conn.conn.cursor() as cursor:
            query = f"""
                with most_recent_batch as (
                  select
                    id
                  from
                    candles
                  where
                    symbol = %(symbol)s
                    and closed_at <= to_timestamp(%(ref_epoch)s)
                    and duration_minutes = %(duration_minutes)s
                  order by
                    opened_at desc
                  limit %(input_width)s
                )
                select
                  {selected_input_columns},
                  id,
                  extract(epoch from opened_at)::float as opened_at_epoch
                from
                  candles
                where
                  id in (
                    select
                      id
                    from
                      most_recent_batch)
                order by
                  opened_at asc
            """

            cursor.execute(
                query,
                {
                    "duration_minutes": self.duration_minutes,
                    "input_width": self.input_width,
                    "ref_epoch": self.ref_epoch,
                    "symbol": self.symbol,
                },
            )

            columns = [c.name for c in cursor.description]
            rows = cursor.fetchall()

        if not len(rows):
            u.ascii.puts("❗ No candles were fetched.", u.ascii.RED)

            sys.exit(1)

        self.inputs = np.array(rows)[:, : len(models.config.SELECTED_INPUT_COLUMNS)]
        self.named_inputs = [dict(zip(columns, row)) for row in rows]

        u.ascii.puts(f"✅ Fetched candles. Shape: {self.inputs.shape}", u.ascii.GREEN)

    def __normalize(self):
        self.inputs_norm = (
            self.inputs - self.norm_factors["mean"]
        ) / self.norm_factors["std"]
