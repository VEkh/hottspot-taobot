import numpy as np
import tensorflow as tf

from . import config


class Baseline(tf.keras.Model):
    def __init__(
        self,
        input_columns=[],
        label_columns=[],
        label_index=None,
        norm_factors=config.DEFAULT_NORM_FACTORS,
    ):
        super().__init__(name="baseline")

        self.input_columns = input_columns
        self.label_columns = label_columns
        self.label_index = label_index
        self.norm_factors = norm_factors

    @classmethod
    def from_config(cls, c):
        config = {**c}
        saved_config = config.pop("saved_config") if "saved_config" in config else {}
        kwargs = cls.__deserialize_config({**config, **saved_config})

        return cls(**{**config, **kwargs})

    @classmethod
    def __deserialize_config(_, config):
        out = {**config}

        if "norm_factors" in config:
            out["norm_factors"] = {
                k: np.array(v) for k, v in config["norm_factors"].items()
            }

        return out

    def call(self, inputs):
        if self.label_index is None:
            return inputs

        result = inputs[:, :, self.label_index]

        return result[:, :, tf.newaxis]

    def get_config(self):
        base_config = super().get_config()

        return {
            **base_config,
            "saved_config": self.__serialize_config(),
        }

    def __serialize_config(self):
        return {
            "input_columns": self.input_columns,
            "label_columns": self.label_columns,
            "label_index": self.label_index,
            "name": self.name,
            "norm_factors": {k: v.tolist() for k, v in self.norm_factors.items()},
        }


def create(**kwargs):
    return Baseline(**kwargs)
