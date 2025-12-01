"""
Choppiness Feature Extractor
=============================
Detects ranging/uncertain market conditions that favor conservative strategies.
Designed to help model recognize "Fold 3 type markets" where rp_id=2 dominates.

Key insight: Fold 3 has:
- Only 44.3% trending (vs 47-51% in other folds)
- High volatility (0.020 vs 0.016-0.018)
- Low regime stability (0.460 vs 0.481-0.523)
- 55.7% optimal rp_id=2 (vs ~45% in other folds)

These features help detect such periods and signal: "Use conservative strategies!"

CRITICAL: All features computed chronologically to prevent look-ahead bias.
"""

import ml.utils as u
import numpy as np
import pandas as pd


class ChoppinessFeatureExtractor:
    def __init__(self):
        self.feature_names_ = None

    def fit(self, raw_data):
        self.feature_names_ = self._generate_feature_names()
        return self

    def fit_transform(self, raw_data):
        return self.fit(raw_data).transform(raw_data)

    def get_feature_names(self):
        if self.feature_names_ is None:
            self.feature_names_ = self._generate_feature_names()

        return self.feature_names_.copy()

    def transform(self, raw_data):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts("🌊  Extracting choppiness features.", u.ascii.CYAN, print_end="")
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        if self.feature_names_ is None:
            raise ValueError("Must call fit() before transform()")

        required_cols = [
            "atr_percentile",
            "avg_true_range_8",
            "consecutive_trending",
            "count_ranging_last_10",
            "count_ranging_last_20",
            "count_ranging_last_5",
            "count_trending_last_10",
            "count_trending_last_20",
            "count_trending_last_5",
            "market_session_id",
            "market_session_opened_at",
            "max_consecutive_either",
            "regime_changes_last_10",
            "regime_changes_last_5",
            "trend_cleanliness",
            "true_range",
        ]

        missing = [col for col in required_cols if col not in raw_data.columns]
        if missing:
            raise ValueError(f"Missing required features: {missing}")

        # Ensure chronological order (critical for time series features)
        data = raw_data.sort_values(
            "market_session_opened_at",
            ascending=True,
        ).reset_index(drop=True)

        features = pd.DataFrame()
        features["market_session_id"] = data["market_session_id"]

        # ================================================================
        # Feature 1-3: ranging_dominance
        # ================================================================
        # Measures how much ranging dominates over trending
        # Positive values = more ranging, negative = more trending
        # Strong signal for rp_id=2 when positive and large

        features["ranging_dominance_short"] = (
            data["count_ranging_last_5"] - data["count_trending_last_5"]
        ) / 5.0

        features["ranging_dominance_medium"] = (
            data["count_ranging_last_10"] - data["count_trending_last_10"]
        ) / 10.0

        features["ranging_dominance_long"] = (
            data["count_ranging_last_20"] - data["count_trending_last_20"]
        ) / 20.0

        # ================================================================
        # Feature 4: volatility_regime_shift
        # ================================================================
        # Detects when volatility spikes during unclear trends
        # High volatility + low trend clarity = dangerous for aggressive strategies
        # Use: atr_percentile (how extreme is current volatility) *
        #      (1 - trend_cleanliness) (how unclear the trend is)

        features["volatility_regime_shift"] = data["atr_percentile"] * (
            1.0 - data["trend_cleanliness"]
        )

        # ================================================================
        # Feature 5: whipsaw_indicator
        # ================================================================
        # Counts how frequently regime switches are happening
        # Many switches = whipsawing market = use conservative strategies
        # Combines short-term and medium-term switching rates

        whipsaw_short = data["regime_changes_last_5"] / 4.0
        whipsaw_medium = data["regime_changes_last_10"] / 9.0

        # Combined indicator: average of short and medium term
        features["whipsaw_indicator"] = (whipsaw_short + whipsaw_medium) / 2.0

        # ================================================================
        # Feature 6: conservative_conditions_met
        # ================================================================
        # Binary flag that explicitly signals when conditions favor rp_id=2
        #
        # Conservative conditions:
        # 1. More ranging than trending (ratio_ranging > 0.5)
        # 2. High volatility (atr_percentile > 0.6)
        #
        # When both are true, conservative strategies typically perform better

        ratio_ranging = data["count_ranging_last_10"] / 10.0

        features["conservative_conditions_met"] = (
            (ratio_ranging > 0.5) & (data["atr_percentile"] > 0.6)
        ).astype(float)

        # ================================================================
        # Feature 7: momentum_exhaustion
        # ================================================================
        # Detects when trending momentum is declining
        #
        # When current consecutive_trending is much lower than the
        # maximum consecutive streak, it suggests trends are weakening
        #
        # Low values (< 0.3) = momentum exhausted = use conservative

        rolling_max_consecutive = (
            pd.concat(
                [data["consecutive_trending"], data["consecutive_ranging"]],
                axis=1,
            )
            .max(axis=1)
            .rolling(window=20, min_periods=5)
            .max()
        )

        features["momentum_exhaustion"] = np.where(
            rolling_max_consecutive > 0,
            data["consecutive_trending"] / rolling_max_consecutive,
            0.5,  # Default to neutral
        )

        # ================================================================
        # Feature 8: volatility_acceleration
        # ================================================================
        # Detects when volatility is rapidly increasing
        #
        # Compares short-term ATR to medium-term ATR
        # Values > 1.2 indicate volatility is accelerating
        # Accelerating volatility often precedes ranging markets

        features["volatility_acceleration"] = np.where(
            data["avg_true_range_8"] > 0,
            data["true_range"] / data["avg_true_range_8"],
            1.0,  # Default to neutral
        )

        # ================================================================
        # Feature 9: regime_uncertainty_score
        # ================================================================
        # Composite score combining multiple uncertainty signals
        #
        # High scores = high uncertainty = favor conservative strategies
        #
        # Components:
        # - whipsaw_indicator (0-1): frequency of regime switches
        # - volatility_regime_shift (0-1): vol spike with unclear trend
        # - ranging_dominance_medium (-1 to +1): ranging vs trending balance

        # Normalize ranging_dominance to 0-1 scale (map -1,+1 to 0,1)
        normalized_ranging = (features["ranging_dominance_medium"] + 1.0) / 2.0

        features["regime_uncertainty_score"] = (
            features["whipsaw_indicator"] * 0.4
            + features["volatility_regime_shift"] * 0.3
            + normalized_ranging * 0.3
        )

        # ================================================================
        # Log feature statistics
        # ================================================================
        u.ascii.puts("\n📊 Choppiness Feature Statistics:", u.ascii.MAGENTA)

        for feature in self.feature_names_:
            mean_val = features[feature].mean()
            std_val = features[feature].std()
            min_val = features[feature].min()
            max_val = features[feature].max()

            u.ascii.puts(
                f"  {feature:30s}: μ={mean_val:6.3f}, σ={std_val:6.3f}, "
                f"range=[{min_val:6.3f}, {max_val:6.3f}]",
                u.ascii.CYAN,
                print_end="",
            )

        conservative_pct = features["conservative_conditions_met"].mean() * 100
        u.ascii.puts(
            f"\n  Conservative conditions met in {conservative_pct:.1f}% of sessions",
            u.ascii.YELLOW,
        )

        u.ascii.puts("\n✅ Choppiness features extracted successfully", u.ascii.GREEN)

        return features

    def _generate_feature_names(self):
        return [
            "conservative_conditions_met",
            "momentum_exhaustion",
            "ranging_dominance_long",
            "ranging_dominance_medium",
            "ranging_dominance_short",
            "regime_uncertainty_score",
            "volatility_acceleration",
            "volatility_regime_shift",
            "whipsaw_indicator",
        ]
