from .feature_loader import FeatureLoader
from .label_loader import LabelLoader
from pathlib import Path
from scipy import stats
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from sklearn.model_selection import TimeSeriesSplit
from sklearn.utils.class_weight import compute_class_weight
import matplotlib.pyplot as plt
import ml.utils as u
import numpy as np
import os
import pandas as pd
import textwrap
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
        self.class_weight_dict = {}
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
        description = textwrap.dedent(
            f"""
        🤖 Training model for predicting {u.ascii.CYAN}{self.symbol}{u.ascii.YELLOW} trade setups.

        ✅ Market Session Duration (Seconds): {self.market_session_duration_seconds}
        ✅ Market Session Warm Up Duration (Seconds): {self.market_session_warm_up_duration_seconds}
        """
        ).strip()

        u.ascii.puts(description, u.ascii.YELLOW)

        self.features = self.feature_loader.load()
        self.label_loader.features = self.features
        self.label_loader.stop_profit_id = 1

        self.labels = self.label_loader.load()

        # TODO: Decide
        # self.label_loader.filter_sparse_classes(min_percentage=0.1)
        # self.labels = self.label_loader.labels

        self.__merge_features_and_labels()
        # self.__analyze_features()  # TODO: Delete
        self.__prepare_data()
        self.__set_class_weights()
        self.__train_single_class_xgboost_model()
        self.__evaluate_model()
        self.__time_series_validation(n_splits=5)
        self.__save_model()

    def __analyze_features(self):
        threshold = 1.0
        print(f"Dataset size after merge: {len(self.features_and_labels)}")

        # Apply the manual rule (note: your code used < for CONSOLIDATION → reverse_id=2)
        self.features_and_labels["manual_rule_prediction"] = self.features_and_labels[
            "warm_up_body_to_wick_ratio"
        ].apply(lambda x: 2 if x < threshold else 1)

        # Calculate accuracy
        accuracy = (
            self.features_and_labels["manual_rule_prediction"]
            == self.features_and_labels["reverse_percentile_id"]
        ).mean()

        print(f"\n{'='*60}")
        print(f"MANUAL RULE VALIDATION (threshold = {threshold})")
        print(f"{'='*60}")
        print(f"Rule accuracy: {accuracy:.2%}")

        # Show label distribution
        print(f"\nActual label distribution:")
        print(self.features_and_labels["reverse_percentile_id"].value_counts())
        print(f"\nActual label distribution (%):")
        print(
            self.features_and_labels["reverse_percentile_id"].value_counts(
                normalize=True
            )
        )

        print(f"\nConfusion Matrix:")
        confusion = pd.crosstab(
            self.features_and_labels["manual_rule_prediction"],
            self.features_and_labels["reverse_percentile_id"],
            rownames=["Predicted (Manual Rule)"],
            colnames=["Actual (Best Performer)"],
            margins=True,
        )
        print(confusion)

        # Crosstab with normalization by columns
        print(f"\nNormalized by actual label (columns):")
        confusion_norm = pd.crosstab(
            self.features_and_labels["manual_rule_prediction"],
            self.features_and_labels["reverse_percentile_id"],
            normalize="columns",
        )
        print(confusion_norm)

        # Distribution statistics by label
        print(f"\nBody-to-wick ratio statistics by reversal strategy:")
        stats_by_label = self.features_and_labels.groupby("reverse_percentile_id")[
            "warm_up_body_to_wick_ratio"
        ].agg(
            [
                "count",
                "mean",
                "std",
                "min",
                ("25%", lambda x: x.quantile(0.25)),
                ("50%", lambda x: x.quantile(0.50)),
                ("75%", lambda x: x.quantile(0.75)),
                "max",
            ]
        )
        print(stats_by_label)

        # Statistical significance test
        group1 = self.features_and_labels[
            self.features_and_labels["reverse_percentile_id"] == 1
        ]["warm_up_body_to_wick_ratio"]
        group2 = self.features_and_labels[
            self.features_and_labels["reverse_percentile_id"] == 2
        ]["warm_up_body_to_wick_ratio"]

        t_stat, p_value = stats.ttest_ind(group1, group2)
        print(f"\nStatistical significance test:")
        print(f"T-statistic: {t_stat:.4f}")
        print(f"P-value: {p_value:.4f}")

        if p_value < 0.05:
            print("✓ Statistically significant relationship detected!")
        else:
            print("✗ No statistically significant relationship")

        # Try different thresholds
        print(f"\n{'='*60}")
        print("TESTING ALTERNATIVE THRESHOLDS")
        print(f"{'='*60}")

        thresholds_to_test = [0.5, 0.8, 1.0, 1.5, 2.0]
        results = []

        for test_threshold in thresholds_to_test:
            test_pred = self.features_and_labels["warm_up_body_to_wick_ratio"].apply(
                lambda x: 2 if x < test_threshold else 1
            )
            test_accuracy = (
                test_pred == self.features_and_labels["reverse_percentile_id"]
            ).mean()
            results.append(
                {"threshold": test_threshold, "accuracy": f"{test_accuracy:.2%}"}
            )

        print(pd.DataFrame(results).to_string(index=False))

        return accuracy

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
            classification_report(self.y_test, self.y_predictions, zero_division=0),
            u.ascii.MAGENTA,
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

        target_column = "reverse_percentile_id"

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
        u.ascii.puts(
            f"Y Train Class Distribution:\n\n{self.y_train.value_counts(normalize=True)}",
            u.ascii.MAGENTA,
        )

    def __save_model(self):
        u.ascii.puts("ℹ  Saving model.", u.ascii.CYAN)

        ml_dir = Path(__file__).resolve().parent.parent.parent
        save_dir = os.path.join(ml_dir, "models", self.symbol)
        os.makedirs(save_dir, exist_ok=True)

        save_path = os.path.join(save_dir, "trade_setup_xgboost_model.json")
        self.model.save_model(save_path)

        u.ascii.puts(f"🎉 Model saved as {save_path}.", u.ascii.GREEN)

    def __set_class_weights(self):
        u.ascii.puts("ℹ  Setting class weights.", u.ascii.CYAN)

        classes = np.unique(self.y_train)
        class_weights = compute_class_weight(
            "balanced",
            classes=classes,
            y=self.y_train,
        )

        self.class_weight_dict = dict(zip(classes, class_weights))

        u.ascii.puts("Class Weights:", u.ascii.MAGENTA)
        u.ascii.puts(f"{self.class_weight_dict}", u.ascii.MAGENTA)

        u.ascii.puts(f"🎉 Finished setting class weights.", u.ascii.GREEN)

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

    def __train_multi_class_xgboost_model(self):
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

        sample_weights = np.array(
            [self.class_weight_dict[label] for label in self.y_train]
        )

        self.model.fit(
            self.X_train,
            self.y_train,
            eval_set=[(self.X_val, self.y_val)],
            sample_weight=sample_weights,
            verbose=True,
        )

        u.ascii.puts("🎉 Finished training XGBClassifier model.", u.ascii.GREEN)

    def __train_single_class_xgboost_model(self):
        u.ascii.puts("ℹ  Training XGBoost model.", u.ascii.CYAN)

        self.model = xgb.XGBClassifier(
            colsample_bytree=0.8,
            early_stopping_rounds=50,
            eval_metric="logloss",
            learning_rate=0.1,
            max_depth=4,
            min_child_weight=3,
            n_estimators=1000,
            objective="binary:logistic",
            random_state=42,
            reg_alpha=0.1,
            reg_lambda=1.0,
            subsample=0.8,
        )

        sample_weights = np.array(
            [self.class_weight_dict[label] for label in self.y_train]
        )

        self.model.fit(
            self.X_train,
            self.y_train,
            eval_set=[(self.X_val, self.y_val)],
            sample_weight=sample_weights,
            verbose=True,
        )

        u.ascii.puts("🎉 Finished training XGBClassifier model.", u.ascii.GREEN)
