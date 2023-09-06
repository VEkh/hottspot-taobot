import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf

from ml.utils import ascii


class WindowGenerator:
    def __init__(
        self,
        input_columns=[],
        input_width=500,
        label_columns=None,
        label_width=1,
        shift=0,
        test_set=np.array([]),
        training_set=np.array([]),
        validation_set=np.array([]),
    ):
        self.input_width = input_width
        self.label_width = label_width
        self.shift = shift
        self.test_set = test_set
        self.training_set = training_set
        self.validation_set = validation_set
        self.label_columns = label_columns

        if label_columns is not None:
            self.label_column_indices = {
                name: i for i, name in enumerate(label_columns)
            }

        self.column_indices = {name: i for i, name in enumerate(input_columns)}

        self.total_window_size = input_width + shift

        self.input_slice = slice(0, input_width)
        self.input_indices = np.arange(self.total_window_size)[self.input_slice]

        self.label_start = self.total_window_size - self.label_width
        self.labels_slice = slice(self.label_start, None)
        self.label_indices = np.arange(self.total_window_size)[self.labels_slice]

    def split_window(self, features):
        inputs = features[:, self.input_slice, :]
        labels = features[:, self.labels_slice, :]

        if self.label_columns is not None:
            labels = tf.stack(
                [
                    labels[:, :, self.column_indices[name]]
                    for name in self.label_columns
                ],
                axis=-1,
            )

        tf.ensure_shape(inputs, [None, self.input_width, None])
        tf.ensure_shape(labels, [None, self.label_width, None])

        return (inputs, labels)

    def __repr__(self):
        message = "\n".join(
            [
                f"Total Window Size:    {self.total_window_size}",
                f"Input Indices:        {self.input_indices}",
                f"Label Indices:        {self.label_indices}",
                f"Label Column Name(s): {self.label_columns}",
            ]
        )

        return message
