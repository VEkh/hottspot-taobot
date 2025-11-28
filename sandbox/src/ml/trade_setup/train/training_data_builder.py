from .base_feature_loader import BaseFeatureLoader
from .choppiness_feature_extractor import ChoppinessFeatureExtractor
from .label_extractor import LabelExtractor
from .label_loader import LabelLoader
from .price_memory_feature_extractor import PriceMemoryFeatureExtractor
from .regime_history_feature_extractor import RegimeHistoryFeatureExtractor
from .trend_quality_feature_extractor import TrendQualityFeatureExtractor
from .volatility_feature_extractor import VolatilityFeatureExtractor
from tabulate import tabulate
import ml.utils as u
import pandas as pd


class TrainingDataBuilder:
    def __init__(
        self,
        db_conn,
        market_session_duration_seconds,
        market_session_warm_up_duration_seconds,
        symbol,
    ):
        self.base_features = []
        self.choppiness_features = pd.DataFrame()
        self.db_conn = db_conn
        self.feature_columns = []
        self.features = pd.DataFrame()
        self.label_mapping = {}
        self.labels = pd.DataFrame()
        self.market_session_duration_seconds = market_session_duration_seconds
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.num_class = 0
        self.price_memory_features = pd.DataFrame()
        self.raw_labels = pd.DataFrame()
        self.regime_history_features = pd.DataFrame()
        self.reverse_label_mapping = {}
        self.symbol = symbol
        self.training_data = pd.DataFrame()
        self.trend_quality_features = pd.DataFrame()
        self.volatility_features = pd.DataFrame()

        self.base_feature_loader = BaseFeatureLoader(
            db_conn=self.db_conn,
            market_session_duration_seconds=self.market_session_duration_seconds,
            market_session_warm_up_duration_seconds=self.market_session_warm_up_duration_seconds,
            symbol=self.symbol,
        )

        self.choppiness_feature_extractor = ChoppinessFeatureExtractor()

        self.label_loader = LabelLoader(db_conn=self.db_conn)
        self.label_extractor = LabelExtractor(confidence_percentile=75.0)

        self.price_memory_feature_extractor = PriceMemoryFeatureExtractor(
            lookback_windows=[1, 3, 5],
            proximity_threshold=0.2,
        )

        self.regime_history_feature_extractor = RegimeHistoryFeatureExtractor(
            lookback_windows=[3, 5, 10, 20],
            ranging_label=2,
            trending_label=1,
        )

        self.trend_quality_feature_extractor = TrendQualityFeatureExtractor()

        self.volatility_feature_extractor = VolatilityFeatureExtractor(
            atr_windows=[4, 8, 14, 26],
            percentile_window=100,
        )

    def build(self):
        self.base_features = self.base_feature_loader.load()
        self.label_loader.market_session_ids = (
            self.base_features["market_session_id"].to_numpy(dtype=int).tolist()
        )

        self.raw_labels = self.label_loader.load()
        self.labels = self.label_extractor.transform(self.raw_labels)

        self.price_memory_features = self.price_memory_feature_extractor.fit_transform(
            self.base_features
        )

        self.regime_history_features = (
            self.regime_history_feature_extractor.fit_transform(self.labels)
        )

        extraction_input_features = pd.merge(
            self.base_features,
            self.labels,
            how="inner",
            on=["market_session_id", "market_session_opened_at"],
        )

        self.volatility_features = self.volatility_feature_extractor.fit_transform(
            extraction_input_features
        )

        extraction_input_features = pd.merge(
            extraction_input_features,
            self.regime_history_features,
            how="inner",
            on="market_session_id",
        )

        extraction_input_features = pd.merge(
            extraction_input_features,
            self.volatility_features,
            how="inner",
            on="market_session_id",
        )

        self.trend_quality_features = (
            self.trend_quality_feature_extractor.fit_transform(
                extraction_input_features
            )
        )

        extraction_input_features = pd.merge(
            extraction_input_features,
            self.trend_quality_features,
            how="inner",
            on="market_session_id",
        )

        self.choppiness_features = self.choppiness_feature_extractor.fit_transform(
            extraction_input_features
        )

        self._merge_features_and_labels()
        self._prepare_data()

    def _merge_features_and_labels(self):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Merging features and labels into training data.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        self.features = pd.merge(
            self.base_features,
            self.regime_history_features,
            how="inner",
            on="market_session_id",
        )

        self.features = pd.merge(
            self.features,
            self.trend_quality_features,
            how="inner",
            on="market_session_id",
        )

        self.features = pd.merge(
            self.features,
            self.price_memory_features,
            how="inner",
            on="market_session_id",
        )

        self.features = pd.merge(
            self.features,
            self.volatility_features,
            how="inner",
            on="market_session_id",
        )

        self.features = pd.merge(
            self.features,
            self.choppiness_features,
            how="inner",
            on="market_session_id",
        )

        self.training_data = pd.merge(
            self.features,
            self.labels,
            how="inner",
            on=["market_session_id", "market_session_opened_at"],
        )

        self.training_data = self.training_data.sort_values(
            "market_session_opened_at",
            ascending=True,
        )

        self.training_data = self.training_data.reset_index(drop=True)

        rows_before = len(self.training_data)
        self.training_data = self.training_data.dropna()
        self.training_data = self.training_data.reset_index(drop=True)
        rows_after = len(self.training_data)

        rows_dropped = rows_before - rows_after
        if rows_dropped > 0:
            u.ascii.puts(
                f"🔔  Dropped {rows_dropped} rows with NaN values (warm-up period)",
                u.ascii.YELLOW,
            )

        u.ascii.puts(self.training_data[:10].to_string(), u.ascii.YELLOW)
        u.ascii.puts("...", u.ascii.YELLOW)
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉 Finished merging features and labels into training data.",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

    def _prepare_data(self):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Preparing training data for model use.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        unique_trade_setups = sorted(self.training_data["trade_setup_id"].unique())

        self.label_mapping = {
            ts_id: idx for idx, ts_id in enumerate(unique_trade_setups)
        }

        self.reverse_label_mapping = {
            idx: ts_id for ts_id, idx in self.label_mapping.items()
        }

        self.num_class = len(self.label_mapping)

        self.training_data["y"] = self.training_data["trade_setup_id"].map(
            self.label_mapping
        )

        u.ascii.puts(f"✔️  Number of classes: {self.num_class}", u.ascii.GREEN)
        u.ascii.puts(f"   Class mapping: {self.label_mapping}", u.ascii.GREEN)

        self._print_class_distribution()

        self.feature_columns = (
            self.base_feature_loader.get_feature_names()
            + self.choppiness_feature_extractor.get_feature_names()
            # + self.regime_history_feature_extractor.get_feature_names()
            # + self.price_memory_feature_extractor.get_feature_names()
            # + self.trend_quality_feature_extractor.get_feature_names()
            # + self.volatility_feature_extractor.get_feature_names()
        )

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉  Finished preparing training data for model use.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"Using {len(self.feature_columns)} features", u.ascii.CYAN)

    def _print_class_distribution(self):
        """Print distribution of target classes"""
        dist = (
            self.training_data.groupby(["y", "trade_setup_id"])
            .size()
            .reset_index(name="count")
        )
        total = len(self.training_data)
        dist["percentage"] = dist["count"] / total * 100

        u.ascii.puts("\nClass Distribution:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            tabulate(
                dist,
                headers="keys",
                showindex=False,
                tablefmt="psql",
            ),
            u.ascii.MAGENTA,
        )
