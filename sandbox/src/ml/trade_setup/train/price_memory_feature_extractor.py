import ml.utils as u
import numpy as np
import pandas as pd


"""
Price Memory Feature Extractor
===============================
Computes features based on the warm-up candle's position relative to previous
sessions' price ranges to capture support/resistance dynamics and price memory.

Key concepts:
- Distance to previous highs/lows (potential resistance/support)
- Overlap with previous ranges (consolidation vs breakout)
- Gap analysis (continuation vs reversal)
- Multi-session context (position within recent trading range)

CRITICAL: All features computed chronologically to prevent look-ahead bias.
"""


class PriceMemoryFeatureExtractor:
    def __init__(
        self,
        lookback_windows=None,
        proximity_threshold=0.2,
    ):
        self.feature_names_ = None
        self.lookback_windows = (
            lookback_windows if lookback_windows is not None else [1, 3, 5]
        )
        self.proximity_threshold = proximity_threshold

    def fit(self, _base_features):
        self.feature_names_ = self._generate_feature_names()

        return self

    def fit_transform(self, base_features):
        return self.fit(base_features).transform(base_features)

    def get_feature_names(self):
        if self.feature_names_ is None:
            self.feature_names_ = self._generate_feature_names()

        return self.feature_names_.copy()

    def transform(self, base_features):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💰 Extracting price memory features from historical ranges...",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        required_cols = [
            "market_session_id",
            "market_session_opened_at",
            "high",
            "low",
            "range",
            "warm_up_high",
            "warm_up_low",
            "warm_up_range",
        ]

        missing_cols = [
            col for col in required_cols if col not in base_features.columns
        ]

        if missing_cols:
            raise ValueError(f"Missing required columns: {missing_cols}")

        data = base_features.copy()
        data = data.sort_values("market_session_opened_at").reset_index(drop=True)

        features = pd.DataFrame(index=data.index)
        features["market_session_id"] = data["market_session_id"].values

        prev_high = data["high"].shift(1)
        prev_low = data["low"].shift(1)
        prev_range = data["range"].shift(1)
        warm_up_high = data["warm_up_high"]
        warm_up_low = data["warm_up_low"]
        warm_up_range = data["warm_up_range"]

        self._compute_previous_session_features(
            data=data,
            features=features,
            prev_high=prev_high,
            prev_low=prev_low,
            prev_range=prev_range,
            warm_up_high=warm_up_high,
            warm_up_low=warm_up_low,
        )

        self._compute_overlap_features(
            data=data,
            features=features,
            prev_high=prev_high,
            prev_low=prev_low,
            prev_range=prev_range,
            warm_up_high=warm_up_high,
            warm_up_low=warm_up_low,
            warm_up_range=warm_up_range,
        )

        self._compute_gap_features(
            data=data,
            features=features,
            prev_high=prev_high,
            prev_low=prev_low,
            prev_range=prev_range,
            warm_up_high=warm_up_high,
            warm_up_low=warm_up_low,
        )

        self._compute_multisession_features(
            data,
            features,
            warm_up_high=warm_up_high,
            warm_up_low=warm_up_low,
        )

        return features

    def _compute_gap_features(
        self,
        data,
        features,
        prev_high,
        prev_low,
        prev_range,
        warm_up_high,
        warm_up_low,
    ):
        gap_up = np.maximum(0, warm_up_low - prev_high)
        features["gap_up_size"] = np.where(prev_range > 0, gap_up / prev_range, 0)

        gap_down = np.maximum(0, prev_low - warm_up_high)
        features["gap_down_size"] = np.where(prev_range > 0, gap_down / prev_range, 0)

    def _compute_multisession_features(
        self,
        data,
        features,
        warm_up_high,
        warm_up_low,
    ):
        warm_up_mid = (warm_up_high + warm_up_low) / 2

        for window in self.lookback_windows:
            if window == 1:
                # Already covered by previous session features
                continue

            # Use shift to exclude current session
            # min_periods=window ensures NaN for insufficient lookback data
            rolling_high = (
                data["high"].shift(1).rolling(window=window, min_periods=window).max()
            )
            rolling_low = (
                data["low"].shift(1).rolling(window=window, min_periods=window).min()
            )
            rolling_range = rolling_high - rolling_low

            def count_overlaps(idx, window_size):
                # Need at least window_size previous sessions
                if idx < window_size:
                    return np.nan

                count = 0
                for i in range(1, window_size + 1):
                    prev_idx = idx - i
                    prev_high = data.loc[prev_idx, "high"]
                    prev_low = data.loc[prev_idx, "low"]
                    current_warm_up_high = data.loc[idx, "warm_up_high"]
                    current_warm_up_low = data.loc[idx, "warm_up_low"]

                    # Check if ranges overlap
                    if not (
                        current_warm_up_high < prev_low
                        or current_warm_up_low > prev_high
                    ):
                        count += 1
                return count

            overlap_counts = [count_overlaps(i, window) for i in range(len(data))]
            features[f"num_overlapping_prev_{window}"] = overlap_counts

            # Position within recent range (-1 = bottom, 0 = middle, +1 = top)
            position = np.where(
                rolling_range > 0,
                ((warm_up_mid - rolling_low) / rolling_range) * 2 - 1,
                0,
            )
            features[f"position_in_prev_{window}_range"] = position

            overlap_low = np.maximum(warm_up_low, rolling_low)
            overlap_high = np.minimum(warm_up_high, rolling_high)
            overlap_range = np.maximum(0, overlap_high - overlap_low)

            warm_up_range = data["warm_up_range"]
            features[f"overlap_pct_prev_{window}"] = np.where(
                warm_up_range > 0, overlap_range / warm_up_range, 0
            )

    def _compute_overlap_features(
        self,
        data,
        features,
        prev_high,
        prev_low,
        prev_range,
        warm_up_high,
        warm_up_low,
        warm_up_range,
    ):
        overlap_low = np.maximum(warm_up_low, prev_low)
        overlap_high = np.minimum(warm_up_high, prev_high)
        overlap_range = np.maximum(0, overlap_high - overlap_low)

        # Division by zero produces inf, but with NaN prev values, result is NaN
        features["overlap_pct_prev_1"] = np.where(
            warm_up_range > 0, overlap_range / warm_up_range, 0
        )

        # Comparison with NaN produces False, which becomes 0 when cast to int
        features["contained_in_prev"] = (
            (warm_up_low >= prev_low) & (warm_up_high <= prev_high)
        ).astype(int)

    def _compute_previous_session_features(
        self,
        data,
        features,
        prev_high,
        prev_low,
        prev_range,
        warm_up_high,
        warm_up_low,
    ):
        # NaN for first row will be handled by downstream dropna()
        features["distance_to_prev_high"] = (prev_high - warm_up_high) / prev_range
        features["distance_to_prev_low"] = (warm_up_low - prev_low) / prev_range

        # Comparison with NaN produces False, which becomes 0 when cast to int
        features["testing_prev_resistance"] = (
            features["distance_to_prev_high"].abs() < self.proximity_threshold
        ).astype(int)

        features["testing_prev_support"] = (
            features["distance_to_prev_low"].abs() < self.proximity_threshold
        ).astype(int)

        # Comparison with NaN produces False, which becomes 0 when cast to int
        features["breaking_above_prev"] = (warm_up_high > prev_high).astype(int)
        features["breaking_below_prev"] = (warm_up_low < prev_low).astype(int)

    def _generate_feature_names(self):
        names = [
            "breaking_above_prev",
            "breaking_below_prev",
            "contained_in_prev",
            "distance_to_prev_high",
            "distance_to_prev_low",
            "gap_down_size",
            "gap_up_size",
            "overlap_pct_prev_1",
            "testing_prev_resistance",
            "testing_prev_support",
        ]

        for window in self.lookback_windows:
            if window >= 2:
                names.extend(
                    [
                        f"num_overlapping_prev_{window}",
                        f"overlap_pct_prev_{window}",
                        f"position_in_prev_{window}_range",
                    ]
                )

        return names
