import ml.utils as u
import pandas as pd
import xgboost as xgb
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
        self.X_test = pd.DataFrame()
        self.X_train = pd.DataFrame()
        self.X_val = pd.DataFrame()
        self.db_conn = db_conn
        self.features = []
        self.features_and_labels = pd.DataFrame()
        self.label_mapping = {}
        self.labels = []
        self.market_session_duration_seconds = market_session_duration_seconds
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.reverse_label_mapping = {}
        self.symbol = symbol
        self.y = pd.DataFrame()
        self.y_test = pd.DataFrame()
        self.y_train = pd.DataFrame()
        self.y_val = pd.DataFrame()

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
        self.__train_xgboost_model()

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

        unique_labels = sorted(self.y.unique())

        self.label_mapping = {label: idx for idx, label in enumerate(unique_labels)}
        self.reverse_label_mapping = {
            idx: label for label, idx in self.label_mapping.items()
        }

        self.y = self.y.map(self.label_mapping)

        split_index = int(0.7 * len(self.X))
        val_split_index = int(0.85 * len(self.X))

        self.X_test = self.X.iloc[val_split_index:]
        self.X_train = self.X.iloc[:split_index]
        self.X_val = self.X.iloc[split_index:val_split_index]
        self.y_test = self.y.iloc[val_split_index:]
        self.y_train = self.y.iloc[:split_index]
        self.y_val = self.y.iloc[split_index:val_split_index]

        u.ascii.puts(f"Features Columns: {feature_columns}", u.ascii.MAGENTA)
        u.ascii.puts(f"X: {self.X.shape[0]} samples", u.ascii.MAGENTA)
        u.ascii.puts(f"Training Set: {self.X_train.shape[0]} samples", u.ascii.MAGENTA)
        u.ascii.puts(f"Validation Set: {self.X_val.shape[0]} samples", u.ascii.MAGENTA)
        u.ascii.puts(f"Test Set: {self.X_test.shape[0]} samples", u.ascii.MAGENTA)

    def __train_xgboost_model(self):
        u.ascii.puts("ℹ  Training XGBoost model.", u.ascii.CYAN)

        model = xgb.XGBClassifier(
            colsample_bytree=0.8,
            early_stopping_rounds=50,
            eval_metric="mlogloss",
            learning_rate=0.1,
            max_depth=4,
            min_child_weight=3,
            n_estimators=1000,
            objective="multi:softprob",
            random_state=42,
            reg_alpha=0.1,
            reg_lambda=1.0,
            subsample=0.8,
        )

        model.fit(
            self.X_train,
            self.y_train,
            eval_set=[(self.X_val, self.y_val)],
            verbose=True,
        )

        u.ascii.puts("🎉 Finished training XGBClassifier model.", u.ascii.GREEN)
