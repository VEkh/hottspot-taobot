import ml.utils as u
import numpy as np
import pandas as pd


"""
Trend Quality Feature Extractor
================================
Computes features that distinguish between:
- Clean trending regimes (favor rp_id=1 - aggressive early entry)
- Choppy/uncertain regimes (favor rp_id=2 - conservative late entry)

These features help the model learn WHEN to use aggressive vs conservative
reversal strategies based on market conditions.

Key insight: It's not just whether the market is trending, but HOW CLEAN
the trend is that determines optimal strategy selection.
"""


class TrendQualityFeatureExtractor:
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
        u.ascii.puts(
            "💡  Extracting trend quality features.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        if self.feature_names_ is None:
            raise ValueError("Must call fit() before transform()")

        required_cols = [
            "avg_true_range_26",
            "avg_true_range_8",
            "consecutive_ranging",
            "consecutive_trending",
            "count_ranging_last_10",
            "count_trending_last_10",
            "market_session_id",
            "market_session_opened_at",
            "max_consecutive_either",
            "regime_changes_last_10",
            "regime_changes_last_5",
            "regime_stability_last_10",
        ]

        missing = [col for col in required_cols if col not in raw_data.columns]

        if missing:
            raise ValueError(f"Missing required features: {missing}")

        data = raw_data.sort_values(
            "market_session_opened_at",
            ascending=True,
        ).reset_index(drop=True)

        features = pd.DataFrame(index=data["market_session_id"])

        # Feature 1: Trend Cleanliness
        # Combines regime stability with low switching rate
        # High value = stable, clean trend
        # Low value = choppy, uncertain market
        features["trend_cleanliness"] = data["regime_stability_last_10"].values * (
            1 - data["regime_changes_last_10"].values / 9
        )

        # Feature 2: Volatility Shock Indicator
        # Binary flag: Is recent volatility significantly higher than normal?
        # 1 = Yes (shock/uncertainty) → favor conservative
        # 0 = No (normal volatility) → can use aggressive
        features["vol_shock_recent"] = (
            data["avg_true_range_8"].values > data["avg_true_range_26"].values * 1.3
        ).astype(float)

        # Feature 3: Regime Switch Acceleration
        # Are regime switches accelerating (increasing uncertainty)?
        # Positive = switches accelerating → market becoming more choppy
        # Negative = switches decelerating → market stabilizing
        features["regime_switch_acceleration"] = (
            data["regime_changes_last_5"].values
            - data["regime_changes_last_10"].values / 2
        )

        # Feature 4a: Regime Persistence
        # How long does the market stay in one regime (trend OR range)?
        # High value = market committed to current regime
        # Low value = frequent regime changes
        divisor = data["max_consecutive_either"].quantile(0.95)
        features["regime_persistence"] = data["max_consecutive_either"].values / divisor

        # Feature 4b: Trend Persistence
        # How long does the market stay in one regime (trend OR range)?
        # High value = market committed to current regime
        # Low value = frequent regime changes
        features["trend_persistence"] = data["consecutive_trending"].values / divisor

        # Feature 4c: Regime Momentum
        # How long does the market stay in one regime (trend OR range)?
        # >0 = Strong trending streak
        # 0 = Just changed regimes
        # <0= Strong ranging streak
        features["regime_momentum"] = np.where(
            data["consecutive_trending"] > 0,
            data["consecutive_trending"].values / divisor,
            -data["consecutive_ranging"].values / divisor,
        )

        # Feature 5: Regime Conviction Score
        # How strongly is the market committing to one regime?
        # High value = clear regime dominance
        # Low value = market is mixed/indecisive
        features["regime_conviction"] = (
            np.abs(
                data["count_trending_last_10"].values
                - data["count_ranging_last_10"].values
            )
            / 10
        )

        return features

    def _generate_feature_names(self):
        return [
            "regime_conviction",
            "regime_momentum",
            "regime_persistence",
            "regime_switch_acceleration",
            "trend_cleanliness",
            "trend_persistence",
            "vol_shock_recent",
        ]
