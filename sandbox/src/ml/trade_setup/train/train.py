from .feature_loader import FeatureLoader
from .label_loader import LabelLoader
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from sklearn.model_selection import TimeSeriesSplit
import matplotlib.pyplot as plt
import ml.utils as u
import numpy as np
import pandas as pd
import xgboost as xgb


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
        self.model = None
        self.reverse_label_mapping = {}
        self.symbol = symbol
        self.y = pd.DataFrame()
        self.y_class_mapped = pd.DataFrame()
        self.y_predictions = None
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
        self.__evaluate_model()
        self.__time_series_validation(n_splits=5)

    def __evaluate_model(self):
        u.ascii.puts("ℹ  Evaluating model.", u.ascii.CYAN)

        if not self.model:
            return

        self.y_predictions = self.model.predict(self.X_test)
        y_predictions_probability = self.model.predict_proba(self.X_test)

        if self.reverse_label_mapping:
            self.y_test = self.y_test.map(self.reverse_label_mapping)
            self.y_predictions = pd.Series(self.y_predictions).map(
                self.reverse_label_mapping
            )

        u.ascii.puts(
            f"Accuracy: {accuracy_score(self.y_test, self.y_predictions):.4f}",
            u.ascii.MAGENTA,
        )

        u.ascii.puts("Classification Report:", u.ascii.MAGENTA)
        u.ascii.puts(
            classification_report(self.y_test, self.y_predictions), u.ascii.MAGENTA
        )

        u.ascii.puts("Confusion Matrix:", u.ascii.MAGENTA)
        u.ascii.puts(
            str(confusion_matrix(self.y_test, self.y_predictions)), u.ascii.MAGENTA
        )

        importance = self.model.feature_importances_
        importance_df = pd.DataFrame(
            {
                "feature": self.feature_loader.columns,
                "importance": importance,
            }
        ).sort_values("importance", ascending=False)

        u.ascii.puts("Feature Importance:", u.ascii.MAGENTA)
        u.ascii.puts(importance_df.to_string(), u.ascii.MAGENTA)

        plt.figure(figsize=(10, 6))
        plt.barh(importance_df["feature"], importance_df["importance"])
        plt.title("Feature Importance")
        plt.xlabel("Importance Score")
        plt.tight_layout()
        plt.savefig(
            f"tmp/{self.symbol}_feature_importance.png", dpi=300, bbox_inches="tight"
        )

        u.ascii.puts("🎉 Finished evaluating model", u.ascii.GREEN)

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

        target_column = "trade_setup_id"

        self.X = self.features_and_labels[self.feature_loader.columns]
        self.y = self.features_and_labels[target_column]

        unique_labels = sorted(self.y.unique())

        self.label_mapping = {label: idx for idx, label in enumerate(unique_labels)}
        self.reverse_label_mapping = {
            idx: label for label, idx in self.label_mapping.items()
        }

        self.y_class_mapped = self.y.map(self.label_mapping)

        # Split data (important: use temporal split for trading data)
        # For time series data, don't shuffle!
        split_index = int(0.7 * len(self.X))
        val_split_index = int(0.85 * len(self.X))

        self.X_test = self.X.iloc[val_split_index:]
        self.X_train = self.X.iloc[:split_index]
        self.X_val = self.X.iloc[split_index:val_split_index]
        self.y_test = self.y_class_mapped.iloc[val_split_index:]
        self.y_train = self.y_class_mapped.iloc[:split_index]
        self.y_val = self.y_class_mapped.iloc[split_index:val_split_index]

        u.ascii.puts(
            f"Features Columns: {self.feature_loader.columns}", u.ascii.MAGENTA
        )
        u.ascii.puts(f"X: {self.X.shape[0]} samples", u.ascii.MAGENTA)
        u.ascii.puts(f"Training Set: {self.X_train.shape[0]} samples", u.ascii.MAGENTA)
        u.ascii.puts(f"Validation Set: {self.X_val.shape[0]} samples", u.ascii.MAGENTA)
        u.ascii.puts(f"Test Set: {self.X_test.shape[0]} samples", u.ascii.MAGENTA)

    def __time_series_validation(self, n_splits=5):
        u.ascii.puts("ℹ  Using TimeSeriesSplit for temporal validation.", u.ascii.CYAN)

        time_series_cv = TimeSeriesSplit(n_splits)
        cross_validation_scores = []

        for train_idx, val_idx in time_series_cv.split(self.X):
            X_train_cv, X_val_cv = self.X.iloc[train_idx], self.X.iloc[val_idx]
            y_train_cv, y_val_cv = (
                self.y_class_mapped.iloc[train_idx],
                self.y_class_mapped.iloc[val_idx],
            )

            model = xgb.XGBClassifier(
                learning_rate=0.1,
                max_depth=4,
                n_estimators=100,
                random_state=42,
            )

            model.fit(X_train_cv, y_train_cv)

            score = model.score(X_val_cv, y_val_cv)
            cross_validation_scores.append(score)

        u.ascii.puts(
            f"Time Series Cross Validation Scores: {cross_validation_scores}",
            u.ascii.MAGENTA,
        )

        u.ascii.puts(
            f"Mean Cross Validation Score: {np.mean(cross_validation_scores):.4f} (+/- {(np.std(cross_validation_scores) * 2):.4f})",
            u.ascii.MAGENTA,
        )
        u.ascii.puts("🎉 Finished time series cross validation.", u.ascii.GREEN)

    def __train_xgboost_model(self):
        u.ascii.puts("ℹ  Training XGBoost model.", u.ascii.CYAN)

        self.model = xgb.XGBClassifier(
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

        self.model.fit(
            self.X_train,
            self.y_train,
            eval_set=[(self.X_val, self.y_val)],
            verbose=True,
        )

        u.ascii.puts("🎉 Finished training XGBClassifier model.", u.ascii.GREEN)
