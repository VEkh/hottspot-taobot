import tensorflow as tf

from . import config
from .compile import compile
from .sequential import Sequential


def create(**kwargs):
    model = Sequential(
        layers=[
            tf.keras.layers.LSTM(return_sequences=True, units=32),
            tf.keras.layers.Dense(
                kernel_initializer=tf.initializers.zeros(),
                units=len(config.LABEL_COLUMNS),
            ),
        ],
        name="lstm",
        **kwargs,
    )

    compile(model)

    return model
