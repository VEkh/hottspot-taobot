import tensorflow as tf


class Baseline(tf.keras.Model):
    def __init__(self, label_index=None, window=None):
        super().__init__()
        self.label_index = label_index

        if window.shift != 1:
            raise ValueError(
                f"Invalid shift: {window.shift}. The Baseline model can only accept a shift of 1."
            )

        self.window = window

    def call(self, inputs):
        label_slice = slice(self.window.labels_slice.start - 1, None)

        if self.label_index is None:
            return inputs[:, label_slice, :]

        result = inputs[:, label_slice, self.label_index]

        return result[:, :, tf.newaxis]
