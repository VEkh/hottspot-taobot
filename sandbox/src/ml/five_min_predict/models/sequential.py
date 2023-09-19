import numpy as np
import tensorflow as tf

from . import config


class Sequential(tf.keras.Sequential):
    def __init__(
        self,
        input_columns=[],
        label_columns=[],
        norm_factors=config.DEFAULT_NORM_FACTORS,
        **kwargs,
    ):
        super().__init__(**kwargs)

        self.input_columns = input_columns
        self.label_columns = label_columns
        self.norm_factors = norm_factors

    @classmethod
    def from_config(cls, conf):
        config = {**conf}
        saved_config = config.pop("saved_config") if "saved_config" in config else {}
        kwargs = cls.__deserialize_config({**config, **saved_config})

        return cls(**kwargs)

    @classmethod
    def __deserialize_config(_, config):
        out = {
            **config,
            "layers": [
                tf.keras.layers.deserialize(v) for v in config.get("layers", [])
            ],
        }

        if "norm_factors" in config:
            out["norm_factors"] = {
                k: np.array([v]) for k, v in config["norm_factors"].items()
            }

        return out

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
            "norm_factors": {k: v.tolist() for k, v in self.norm_factors.items()},
        }
