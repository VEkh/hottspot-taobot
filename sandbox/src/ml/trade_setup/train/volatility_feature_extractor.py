import ml.utils as u
import numpy as np
import pandas as pd

"""
Volatility Feature Extractor
==============================
Computes volatility-based features from true_range data to capture market regime
characteristics and gap behavior across multiple time horizons.

CRITICAL: All features are computed chronologically to prevent look-ahead bias.
"""


class VolatilityFeatureExtractor:
    def __init__(
        self,
        atr_windows=None,
        percentile_window=100,
    ):
        self.atr_windows = atr_windows if atr_windows is not None else [4, 8, 14, 26]
        self.feature_names_ = None
        self.percentile_window = percentile_window

    def fit(self, data):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "📊  Extracting volatility features from true ranges.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        self.feature_names_ = self._generate_feature_names()

        return self

    def fit_transform(self, data):
        return self.fit(data).transform(data)

    def get_feature_names(self):
        if self.feature_names_ is None:
            self.feature_names_ = self._generate_feature_names()

        return self.feature_names_.copy()

    def transform(self, data):
        if self.feature_names_ is None:
            self.fit(data)

        if not isinstance(data, pd.DataFrame):
            raise TypeError("Input must be a pandas DataFrame with required columns")

        required_cols = [
            "market_session_id",
            "market_session_opened_at",
            "true_range",
            "warm_up_range",
            "warm_up_true_range",
        ]

        missing_cols = [col for col in required_cols if col not in data.columns]

        if missing_cols:
            raise ValueError(f"Missing required columns: {missing_cols}")

        data_sorted = data.sort_values(
            "market_session_opened_at",
            ascending=True,
        ).reset_index(drop=True)

        features = pd.DataFrame()
        features["market_session_id"] = data_sorted["market_session_id"]

        # === LAYER 1: AVERAGE TRUE RANGE AT MULTIPLE HORIZONS ===
        for window in self.atr_windows:
            col_name = f"avg_true_range_{window}"

            features[col_name] = (
                data_sorted["true_range"]
                .rolling(
                    window=window,
                    min_periods=window,  # Only compute when we have full window
                )
                .mean()
            )

        # === LAYER 2: VOLATILITY REGIME INDICATORS ===
        # Compute short-term indicators (recent changes)
        if 4 in self.atr_windows and 8 in self.atr_windows:
            features["atr_ratio_short"] = (
                features["avg_true_range_4"] / features["avg_true_range_8"]
            )

            features["volatility_momentum_short"] = (
                features["avg_true_range_4"] - features["avg_true_range_8"]
            ) / features["avg_true_range_8"]

        # Compute long-term indicators (trend changes)
        if 14 in self.atr_windows and 26 in self.atr_windows:
            features["atr_ratio_long"] = (
                features["avg_true_range_14"] / features["avg_true_range_26"]
            )

            features["volatility_momentum_long"] = (
                features["avg_true_range_14"] - features["avg_true_range_26"]
            ) / features["avg_true_range_26"]

        # === LAYER 3: HISTORICAL VOLATILITY CONTEXT ===
        if 26 in self.atr_windows:
            features["atr_percentile"] = (
                features["avg_true_range_26"]
                .rolling(
                    window=self.percentile_window,
                    min_periods=26,  # Need reasonable history to compute percentile
                )
                .rank(pct=True)
            )

        # === LAYER 4: WARM-UP PERIOD VOLATILITY ===
        if 26 in self.atr_windows:
            # Normalized warm-up true range: How volatile was warm-up vs typical?
            # Value of 1.5 = warm-up was 50% more volatile than normal
            features["normalized_warm_up_true_range"] = (
                data_sorted["warm_up_true_range"] / features["avg_true_range_26"]
            )

        # === LAYER 5: GAP DETECTION ===
        # Gap ratio: warm_up_true_range / warm_up_range
        # ~1.0 = no gap, >>1.0 = significant gap from previous session
        # Handle division by zero (though should be filtered in SQL)
        features["warm_up_gap_ratio"] = np.where(
            data_sorted["warm_up_range"] > 0,
            data_sorted["warm_up_true_range"] / data_sorted["warm_up_range"],
            1.0,  # Default to no gap if range is zero
        )

        return features

    def _generate_feature_names(self):
        names = []

        # Layer 1: ATR at different horizons
        for window in self.atr_windows:
            names.append(f"avg_true_range_{window}")

        # Layer 2: Regime indicators (short-term and long-term)
        if 4 in self.atr_windows and 8 in self.atr_windows:
            names.extend(
                [
                    "atr_ratio_short",
                    "volatility_momentum_short",
                ]
            )

        if 14 in self.atr_windows and 26 in self.atr_windows:
            names.extend(
                [
                    "atr_ratio_long",
                    "volatility_momentum_long",
                ]
            )
        # Layer 3: Historical context
        if 26 in self.atr_windows:
            names.append("atr_percentile")

        # Layer 4: Warm-up volatility
        if 26 in self.atr_windows:
            names.append("normalized_warm_up_true_range")

        # Layer 5: Gap detection
        names.append("warm_up_gap_ratio")

        return names
