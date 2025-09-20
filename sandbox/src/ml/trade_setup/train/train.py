import ml.utils as u
import pandas as pd
from .feature_loader import FeatureLoader
from .label_loader import LabelLoader


class Train:
    def __init__(
        self,
        db_conn=None,
        market_session_duration_seconds=0,
        market_session_warm_up_duration_seconds=0,
        symbol=None,
    ):
        self.X = pd.DataFrame()
        self.db_conn = db_conn
        self.features = []
        self.features_and_labels = pd.DataFrame()
        self.market_session_duration_seconds = market_session_duration_seconds
        self.labels = []
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.symbol = symbol
        self.y = pd.DataFrame()

        self.feature_loader = FeatureLoader(
            db_conn=self.db_conn,
            market_session_duration_seconds=self.market_session_duration_seconds,
            market_session_warm_up_duration_seconds=self.market_session_warm_up_duration_seconds,
            symbol=self.symbol,
        )

        self.label_loader = LabelLoader(
            db_conn=self.db_conn,
            features=self.features,
        )

    def run(self):
        description = f"""
        🤖 Training model for predicting {u.ascii.CYAN}{self.symbol}{u.ascii.YELLOW} trade setups.

        ✅ Market Session Duration (Seconds): {self.market_session_duration_seconds}
        ✅ Market Session Warm Up Duration (Seconds): {self.market_session_warm_up_duration_seconds}
        """

        u.ascii.puts(description, u.ascii.YELLOW)

        self.features = self.feature_loader.load()
        self.label_loader.features = self.features

        self.labels = self.label_loader.load()
        self.label_loader.filter_sparse_classes(min_percentage=0.1)
        self.labels = self.label_loader.labels

        self.__merge_features_and_labels()
        self.__prepare_data()

    def __merge_features_and_labels(self):
        u.ascii.puts("ℹ  Merging features and labels.", u.ascii.CYAN)

        self.features_and_labels = pd.merge(
            self.features,
            self.labels,
            how="inner",
            on="market_session_id",
        )

        u.ascii.puts(self.features_and_labels[:10].to_string(), u.ascii.YELLOW)
        u.ascii.puts("...", u.ascii.YELLOW)
        u.ascii.puts("🎉 Finished merging features and labels.", u.ascii.GREEN)

    def __prepare_data(self):
        u.ascii.puts("ℹ  Prepare data for model.", u.ascii.CYAN)

        feature_columns = [
            "warm_up_body_to_range_ratio",
            "warm_up_body_to_lower_wick_ratio",
            "warm_up_body_to_upper_wick_ratio",
        ]

        target_column = "trade_setup_id"

        self.X = self.features_and_labels[feature_columns]
        self.y = self.features_and_labels[target_column]

        u.ascii.puts(f"Features Columns: {feature_columns}", u.ascii.MAGENTA)
        u.ascii.puts(f"Features Shape: {self.X.shape}", u.ascii.MAGENTA)
        u.ascii.puts(f"Target Distribution:\n{self.y.value_counts()}", u.ascii.MAGENTA)

    def __train_xgboost_model(self):
        u.ascii.puts("ℹ  Training XGBoost model.", u.ascii.CYAN)
