import ml.utils as u
import numpy as np
import pandas as pd


"""
Regime History Feature Extractor
==================================
Computes features based on historical regime labels (rp_id) to predict
whether the current session will be trending (rp_id=1) or ranging (rp_id=2).

CRITICAL: Prevents label leakage by only using past session labels.
"""


class RegimeHistoryFeatureExtractor:
    def __init__(
        self,
        lookback_windows=None,
        ranging_label=2,
        trending_label=1,
    ):
        self.feature_names_ = None
        self.lookback_windows = lookback_windows if lookback_windows is not None else [3, 5, 10, 20]
        self.ranging_label = ranging_label
        self.trending_label = trending_label

    # Keep unused data arg to maintain scikit convention
    def fit(self, data):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Extracting regime history features from labels.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        self.feature_names_ = self._generate_feature_names()
        return self

    def fit_transform(self, labels):
        return self.fit(labels).transform(labels)

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
            "reverse_percentile_id",
        ]

        missing_cols = [col for col in required_cols if col not in data.columns]

        if missing_cols:
            raise ValueError(f"Missing required columns: {missing_cols}")

        # Sort by time to ensure chronological order (oldest to newest)
        # This is CRITICAL - features must be computed in time order
        data_sorted = data.sort_values(
            "market_session_opened_at", ascending=True
        ).reset_index(drop=True)

        session_ids = data_sorted["market_session_id"].values
        labels = data_sorted["reverse_percentile_id"].values

        n_sessions = len(labels)
        features = pd.DataFrame()

        features["market_session_id"] = session_ids

        for i in range(n_sessions):
            session_features = self._compute_session_features(
                current_idx=i,
                label_array=labels,
            )

            for feat_name, feat_value in session_features.items():
                features.loc[i, feat_name] = feat_value

        return features

    def _compute_session_features(self, current_idx=0, label_array=None):
        if label_array is None:
            label_array = np.array([])

        features = {}

        # Can't compute features for first session (no history)
        if current_idx == 0:
            return self._get_null_features()

        # Get past labels only (exclude current session)
        past_labels = label_array[:current_idx]

        # === LAYER 1: COUNTS AND RATIOS ===
        for window in self.lookback_windows:
            window_labels = (
                past_labels[-window:] if len(past_labels) >= window else past_labels
            )

            if len(window_labels) > 0:
                count_ranging = np.sum(window_labels == self.ranging_label)
                count_trending = np.sum(window_labels == self.trending_label)

                features[f"count_ranging_last_{window}"] = count_ranging
                features[f"count_trending_last_{window}"] = count_trending

                features[f"ratio_ranging_last_{window}"] = count_ranging / len(
                    window_labels
                )
                features[f"ratio_trending_last_{window}"] = count_trending / len(
                    window_labels
                )
            else:
                features[f"count_ranging_last_{window}"] = 0
                features[f"count_trending_last_{window}"] = 0
                features[f"ratio_ranging_last_{window}"] = 0.0
                features[f"ratio_trending_last_{window}"] = 0.0

        # === LAYER 2: STREAK DETECTION ===
        consecutive_ranging = self._count_consecutive(
            labels=past_labels,
            target_label=self.ranging_label,
        )

        consecutive_trending = self._count_consecutive(
            labels=past_labels,
            target_label=self.trending_label,
        )

        features["consecutive_ranging"] = consecutive_ranging
        features["consecutive_trending"] = consecutive_trending
        features["max_consecutive_either"] = max(
            consecutive_trending, consecutive_ranging
        )

        features["sessions_since_regime_change"] = self._sessions_since_change(
            past_labels
        )

        # === LAYER 3: REGIME TRANSITIONS ===
        if len(past_labels) >= 2:
            features["regime_just_switched"] = int(past_labels[-1] != past_labels[-2])

            for window in self.lookback_windows:
                if window >= 2:  # Need at least 2 sessions to detect a change
                    if len(past_labels) >= window:
                        window_labels = past_labels[-window:]
                        changes = np.sum(window_labels[1:] != window_labels[:-1])
                        features[f"regime_changes_last_{window}"] = changes
                        features[f"regime_stability_last_{window}"] = 1 - (
                            changes / (window - 1)
                        )
                    else:
                        features[f"regime_changes_last_{window}"] = 0
                        features[f"regime_stability_last_{window}"] = 1.0
        else:
            features["regime_just_switched"] = 0

            for window in self.lookback_windows:
                if window >= 2:
                    features[f"regime_changes_last_{window}"] = 0
                    features[f"regime_stability_last_{window}"] = 1.0

        # === LAYER 4: WEIGHTED HISTORY ===
        features["exponential_trending_score"] = self._exponential_regime_score(
            alpha=0.3,
            labels=past_labels,
            target_label=self.trending_label,
        )

        # Recent vs distant comparison (are recent sessions more trending?)
        if len(past_labels) >= 10:
            recent_trending_ratio = np.mean(past_labels[-5:] == self.trending_label)
            distant_trending_ratio = np.mean(past_labels[-10:-5] == self.trending_label)
            features["trending_momentum"] = (
                recent_trending_ratio - distant_trending_ratio
            )
        else:
            features["trending_momentum"] = 0.0

        return features

    def _count_consecutive(self, labels=None, target_label=0):
        if labels is None:
            labels = np.array([])

        if len(labels) == 0:
            return 0

        count = 0

        for i in range(len(labels) - 1, -1, -1):
            if labels[i] == target_label:
                count += 1
            else:
                break

        return count

    def _exponential_regime_score(
        self,
        alpha=0.3,
        labels=None,
        target_label=0,
    ):
        """
        Compute exponentially weighted score for a regime.
        Recent sessions weighted more heavily.

        Higher alpha = More weight to recent

        Returns value between 0 and 1 (higher = more of target regime recently)
        """
        if labels is None:
            labels = np.array([])

        if len(labels) == 0:
            return 0.0

        # Convert to binary (1 if target_label, 0 otherwise)
        binary = (labels == target_label).astype(float)

        exp_moving_avg = binary[0]
        for value in binary[1:]:
            exp_moving_avg = alpha * value + (1 - alpha) * exp_moving_avg

        return exp_moving_avg

    def _generate_feature_names(self):
        names = []

        # Layer 1: Counts and ratios
        for window in self.lookback_windows:
            names.extend(
                [
                    f"count_ranging_last_{window}",
                    f"count_trending_last_{window}",
                    f"ratio_ranging_last_{window}",
                    f"ratio_trending_last_{window}",
                ]
            )

        # Layer 2: Streaks
        names.extend(
            [
                "consecutive_ranging",
                "consecutive_trending",
                "max_consecutive_either",
                "sessions_since_regime_change",
            ]
        )

        # Layer 3: Transitions
        names.append("regime_just_switched")

        for window in self.lookback_windows:
            if window >= 2:
                names.extend(
                    [
                        f"regime_changes_last_{window}",
                        f"regime_stability_last_{window}",
                    ]
                )

        # Layer 4: Weighted history
        names.extend(
            [
                "exponential_trending_score",
                "trending_momentum",
            ]
        )

        return names

    def _get_null_features(self):
        if self.feature_names_ is None:
            self.feature_names_ = self._generate_feature_names()

        return {name: 0.0 for name in self.feature_names_}

    def _sessions_since_change(self, labels):
        if len(labels) <= 1:
            return len(labels)

        for i in range(len(labels) - 1, 0, -1):
            if labels[i] != labels[i - 1]:
                return len(labels) - i

        # No change found in entire history
        return len(labels)
