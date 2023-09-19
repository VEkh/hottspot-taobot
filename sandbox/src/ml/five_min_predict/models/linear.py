import numpy as np
import tensorflow as tf

from . import config
from .compile import compile
from .sequential import Sequential


def create(**kwargs):
    model = Sequential(
        layers=[tf.keras.layers.Dense(units=len(config.LABEL_COLUMNS))],
        name="linear",
        **kwargs,
    )

    compile(model)

    return model
