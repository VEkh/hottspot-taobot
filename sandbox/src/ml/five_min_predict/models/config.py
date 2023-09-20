import numpy as np

CONVOLUTION_SIZE = 3

DEFAULT_NORM_FACTORS = {"mean": np.array([]), "std": np.array([])}

INPUT_WIDTH = 150

LABEL_COLUMNS = [
    "close",
    "high",
    "low",
    "open",
]

SELECTED_INPUT_COLUMNS = [
    "close",
    "high",
    "low",
    "open",
    "cos((extract(epoch from opened_at) * pi()) /(24 * 60 * 60)) as opened_at_day_cos",
    "sin((extract(epoch from opened_at) * pi()) /(24 * 60 * 60)) as opened_at_day_sin",
]
