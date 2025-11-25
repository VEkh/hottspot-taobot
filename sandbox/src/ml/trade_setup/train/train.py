from .feature_eliminator import FeatureEliminator
from .trainer import Trainer
from .training_data_builder import TrainingDataBuilder
import ml.utils as u
import textwrap
import time


class Train:
    def __init__(
        self,
        db_conn,
        eliminate_features,
        market_session_duration_seconds,
        market_session_warm_up_duration_seconds,
        symbol,
    ):
        self.eliminate_features = eliminate_features
        self.market_session_duration_seconds = market_session_duration_seconds
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.start_epoch = time.time()
        self.symbol = symbol

        self.training_data_builder = TrainingDataBuilder(
            db_conn=db_conn,
            market_session_duration_seconds=market_session_duration_seconds,
            market_session_warm_up_duration_seconds=market_session_warm_up_duration_seconds,
            symbol=symbol,
        )

    def run(self):
        description = textwrap.dedent(
            f"""
        🤖 Training model for predicting {u.ascii.CYAN}{self.symbol}{u.ascii.YELLOW} trade setups.

        Market Session Duration (Seconds): {self.market_session_duration_seconds}
        Market Session Warm Up Duration (Seconds): {self.market_session_warm_up_duration_seconds}
        """
        ).strip()

        u.ascii.puts(description, u.ascii.YELLOW)

        self.training_data_builder.build()

        excluded_features = [
            "atr_ratio_long",
            "avg_true_range_14",
            "avg_true_range_4",
            "consecutive_ranging",
            "count_ranging_last_10",
            "count_ranging_last_3",
            "count_ranging_last_5",
            "count_trending_last_10",
            "count_trending_last_5",
            "exponential_trending_score",
            "normalized_warm_up_true_range",
            "ratio_trending_last_10",
            "ratio_trending_last_5",
            "regime_changes_last_20",
            "regime_changes_last_5",
            "regime_stability_last_5",
            "sessions_since_regime_change",
            "trending_momentum",
            "volatility_momentum_long",
            "warm_up_body_to_upper_wick_ratio",
            "warm_up_true_range",
        ]

        if self.eliminate_features:
            feature_eliminator = FeatureEliminator(
                init_features_removed=excluded_features,
                training_data_builder=self.training_data_builder,
            )

            feature_eliminator.run()
            excluded_features = feature_eliminator.features_removed

        trainer = Trainer(
            excluded_features=excluded_features,
            training_data_builder=self.training_data_builder,
        )

        trainer.train_with_cv()
        u.time.log_duration(end=time.time(), start=self.start_epoch)
