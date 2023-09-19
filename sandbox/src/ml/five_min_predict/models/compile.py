import tensorflow as tf


def compile(model):
    model.compile(
        loss=tf.keras.losses.MeanSquaredError(),
        metrics=[tf.keras.metrics.MeanAbsoluteError()],
        optimizer=tf.keras.optimizers.Adam(),
    )
