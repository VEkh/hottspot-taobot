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

    @property
    def example(self):
        """Get and cache an example batch of `inputs, labels` for plotting."""
        result = getattr(self, "_example", None)

        if result is None:
            result = next(iter(self.train))
            self._example = result

        return result

    @property
    def test(self):
        return self.make_dataset(self.test_set)

    @property
    def train(self):
        return self.make_dataset(self.training_set)

    @property
    def validation(self):
        return self.make_dataset(self.validation_set)

    def make_dataset(self, data):
        data = np.array(data, dtype=np.float32)

        return tf.keras.utils.timeseries_dataset_from_array(
            batch_size=32,
            data=data,
            sequence_length=self.total_window_size,
            sequence_stride=1,
            shuffle=True,
            targets=None,
        ).map(self.split_window)

    def plot(self, filename="plot.png", max_subplots=3, model=None, plot_column=""):
        mpl.rcParams["axes.grid"] = False
        mpl.rcParams["figure.figsize"] = (8, 6)

        inputs, labels = self.example
        plt.figure(figsize=(12, 8))
        plot_column_index = self.column_indices[plot_column]

        max_n = min(max_subplots, len(inputs))

        for n in range(max_n):
            plt.subplot(max_n, 1, n + 1)
            plt.ylabel(f"{plot_column} [normed]")
            plt.plot(
                self.input_indices,
                inputs[n, :, plot_column_index],
                label="Inputs",
                marker=".",
                zorder=-10,
            )

            if self.label_columns:
                label_column_index = self.label_column_indices.get(plot_column, None)
            else:
                label_column_index = plot_column_index

            plt.scatter(
                self.label_indices,
                labels[n, :, label_column_index],
                c="#2ca02c",
                edgecolors="k",
                label="Labels",
                marker="X",
                s=64,
            )

            if model is not None:
                predictions = model(inputs)

                plt.scatter(
                    self.label_indices,
                    predictions[n, : len(self.label_indices), label_column_index],
                    c="#ff7f0e",
                    edgecolors="k",
                    label="Predictions",
                    marker="X",
                    s=64,
                )

            if n == 0:
                plt.legend()

        plt.xlabel("Time [5 min]")
        savepath = f"tmp/{filename}"

        plt.savefig(savepath)
        plt.clf()

        ascii.puts(f"📊 Plot saved to {ascii.CYAN}{savepath}.", ascii.YELLOW)

    def split_window(self, batch):
        inputs = batch[:, self.input_slice, :]
        labels = batch[:, self.labels_slice, :]

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
