import tensorflow as tf

from . import config
from .compile import compile
from .sequential import Sequential


def create(**kwargs):
    model = Sequential(
        layers=[
            tf.keras.layers.Conv1D(
                activation="relu",
                filters=32,
                kernel_size=(config.CONVOLUTION_SIZE,),
            ),
            tf.keras.layers.Dense(activation="relu", units=32),
            tf.keras.layers.Dense(units=len(config.LABEL_COLUMNS)),
        ],
        name="convolutional",
        **kwargs,
    )

    compile(model)

    return model
