from .feature_loader import FeatureLoader
from .label_builder import LabelBuilder
from .label_loader import LabelLoader
from .regime_history_feature_extractor import RegimeHistoryFeatureExtractor
from .weighted_model import WeightedModel
from pathlib import Path
from scipy import stats
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from sklearn.model_selection import TimeSeriesSplit, train_test_split
from sklearn.utils.class_weight import compute_class_weight
import json
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
        self.confidence_scores = pd.DataFrame()
        self.confidence_test = pd.DataFrame()
        self.confidence_train = pd.DataFrame()
        self.confidence_val = pd.DataFrame()
        self.db_conn = db_conn
        self.feature_columns = []
        self.features = []
        self.training_data = pd.DataFrame()
        self.label_mapping = {}
        self.labels = []
        self.market_session_duration_seconds = market_session_duration_seconds
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.regime_history_features = pd.DataFrame()
        self.reverse_label_mapping = {}
        self.symbol = symbol
        self.y = pd.DataFrame()
        self.y_class_mapped = pd.DataFrame()
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

        self.label_builder = LabelBuilder()

        self.regime_history_feature_extractor = RegimeHistoryFeatureExtractor(
            lookback_windows=[3, 5, 10, 20],
            ranging_label=2,
            trending_label=1,
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

        self.label_loader.load()
        self.labels = self.label_builder.build(self.label_loader.labels)
        self.regime_history_features = (
            self.regime_history_feature_extractor.fit_transform(self.labels)
        )

        self._merge_features_and_labels()
        # self._analyze_features()  # TODO: Delete
        feature_elimination_results = self._greedy_backward_feature_elimination()

        self._evaluate_feature_subset(
            exclude=feature_elimination_results["excluded_features"]
        )
        # self._save_model()

    def _analyze_features(self):
        threshold = 1.0
        print(f"Dataset size after merge: {len(self.training_data)}")

        print("\nFeature distributions by class:")
        for feature in self.feature_columns:
            print(f"\n{feature}:")
            print(
                self.training_data.groupby("reverse_percentile_id")[feature].describe()
            )

        # Apply the manual rule (note: your code used < for CONSOLIDATION → reverse_id=2)
        self.training_data["manual_rule_prediction"] = self.training_data[
            "warm_up_body_to_wick_ratio"
        ].apply(lambda x: 2 if x < threshold else 1)

        # Calculate accuracy
        accuracy = (
            self.training_data["manual_rule_prediction"]
            == self.training_data["reverse_percentile_id"]
        ).mean()

        print(f"\n{'='*60}")
        print(f"MANUAL RULE VALIDATION (threshold = {threshold})")
        print(f"{'='*60}")
        print(f"Rule accuracy: {accuracy:.2%}")

        # Show label distribution
        print(f"\nActual label distribution:")
        print(self.training_data["reverse_percentile_id"].value_counts())
        print(f"\nActual label distribution (%):")
        print(self.training_data["reverse_percentile_id"].value_counts(normalize=True))

        print(f"\nConfusion Matrix:")
        confusion = pd.crosstab(
            self.training_data["manual_rule_prediction"],
            self.training_data["reverse_percentile_id"],
            rownames=["Predicted (Manual Rule)"],
            colnames=["Actual (Best Performer)"],
            margins=True,
        )
        print(confusion)

        # Crosstab with normalization by columns
        print(f"\nNormalized by actual label (columns):")
        confusion_norm = pd.crosstab(
            self.training_data["manual_rule_prediction"],
            self.training_data["reverse_percentile_id"],
            normalize="columns",
        )
        print(confusion_norm)

        # Distribution statistics by label
        print(f"\nBody-to-wick ratio statistics by reversal strategy:")
        stats_by_label = self.training_data.groupby("reverse_percentile_id")[
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
        group1 = self.training_data[self.training_data["reverse_percentile_id"] == 1][
            "warm_up_body_to_wick_ratio"
        ]
        group2 = self.training_data[self.training_data["reverse_percentile_id"] == 2][
            "warm_up_body_to_wick_ratio"
        ]

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
            test_pred = self.training_data["warm_up_body_to_wick_ratio"].apply(
                lambda x: 2 if x < test_threshold else 1
            )
            test_accuracy = (
                test_pred == self.training_data["reverse_percentile_id"]
            ).mean()
            results.append(
                {"threshold": test_threshold, "accuracy": f"{test_accuracy:.2%}"}
            )

        print(pd.DataFrame(results).to_string(index=False))

        return accuracy

    def _calculate_trading_metrics(
        self,
        profit_loss_data=None,
        y_predictions=None,
        y_true=None,
    ):
        if profit_loss_data is None:
            profit_loss_data = pd.DataFrame()
        if y_predictions is None:
            y_predictions = pd.DataFrame()
        if y_true is None:
            y_true = pd.DataFrame()

        unmapped_y_predictions = (
            pd.Series(y_predictions, name="unmapped_y_predictions")
            .map(self.reverse_label_mapping)
            .to_numpy(dtype=int)
        )

        unmapped_y_true = (
            pd.Series(y_true, name="unmapped_y_true")
            .map(self.reverse_label_mapping)
            .to_numpy(dtype=int)
        )

        actual_profit_losses = []
        predicted_profit_losses = []

        for i in range(len(unmapped_y_true)):
            session_data = profit_loss_data.iloc[i]

            # P&L if we followed true best strategy
            true_strategy = unmapped_y_true[i]
            actual_profit_losses.append(
                session_data[f"profit_loss_percent_{true_strategy}"]
            )

            # P&L if we followed predicted strategy
            predicted_strategy = unmapped_y_predictions[i]
            predicted_profit_losses.append(
                session_data[f"profit_loss_percent_{predicted_strategy}"]
            )

        cumulative_predicted = np.cumsum(predicted_profit_losses)

        total_return_actual = sum(actual_profit_losses)
        total_return_predicted = sum(predicted_profit_losses)
        return_capture = (total_return_predicted / total_return_actual) * 100

        running_max_predicted = np.maximum.accumulate(cumulative_predicted)
        drawdown_predicted = running_max_predicted - cumulative_predicted
        max_drawdown_predicted = (
            np.max(drawdown_predicted) if len(drawdown_predicted) > 0 else 0
        )

        # Sharpe ratio (annualized, assuming weekly data)
        if len(predicted_profit_losses) > 1:
            returns_std = np.std(predicted_profit_losses)

            if returns_std > 0:
                sharpe_predicted = (
                    np.mean(predicted_profit_losses) / returns_std
                ) * np.sqrt(52)
            else:
                sharpe_predicted = 0
        else:
            sharpe_predicted = 0

        u.ascii.puts("=" * 60, u.ascii.MAGENTA, print_end="")
        u.ascii.puts("TRADING PERFORMANCE METRICS", u.ascii.MAGENTA, print_end="")
        u.ascii.puts("=" * 60, u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"Optimal Strategy Return: ${total_return_actual:,.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Model Strategy Return: ${total_return_predicted:,.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Return Capture: {(total_return_predicted/total_return_actual)*100:.1f}%",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Max Drawdown: ${max_drawdown_predicted:,.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Sharpe Ratio: {sharpe_predicted:.3f}", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts("=" * 60, u.ascii.MAGENTA)

        return return_capture

    def _evaluate_feature_subset(self, exclude=None):
        if exclude is None:
            exclude = []

        self._prepare_data(exclude=exclude)
        profit_loss_data = self.training_data.iloc[self.X_test.index][
            ["profit_loss_percent_1", "profit_loss_percent_2"]
        ]

        class_weighted_model_class = self._train_class_weighted_model()
        self._evaluate_model(class_weighted_model_class)
        class_weighted_return_capture = self._calculate_trading_metrics(
            profit_loss_data=profit_loss_data,
            y_predictions=class_weighted_model_class.predictions,
            y_true=self.y_test,
        )

        confidence_weighted_model_class = self._train_confidence_weighted_model()
        self._evaluate_model(confidence_weighted_model_class)
        confidence_weighted_return_capture = self._calculate_trading_metrics(
            profit_loss_data=profit_loss_data,
            y_predictions=confidence_weighted_model_class.predictions,
            y_true=self.y_test,
        )

        self._time_series_validation(n_splits=5)

        return {
            "class_weighted": class_weighted_return_capture,
            "confidence_weighted": confidence_weighted_return_capture,
        }

    def _evaluate_model(self, model_class=None):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts("💡  Evaluating model", u.ascii.CYAN, print_end="")
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        if model_class is None:
            u.ascii.puts(
                "！ Failed to evaluate model. model_class is empty",
                u.ascii.RED,
            )

            return

        model = model_class.model

        if model is None:
            u.ascii.puts(
                "！ Failed to evaluate model. model is empty",
                u.ascii.RED,
            )

            return

        y_predictions = model_class.predict(self.X_test)
        y_test = self.y_test

        if self.reverse_label_mapping:
            y_test = y_test.map(self.reverse_label_mapping)
            y_predictions = pd.Series(y_predictions).map(self.reverse_label_mapping)

        u.ascii.puts(
            f"Accuracy: {accuracy_score(y_test, y_predictions):.4f}",
            u.ascii.MAGENTA,
        )

        u.ascii.puts("Classification Report:", u.ascii.MAGENTA)
        u.ascii.puts(
            classification_report(y_test, y_predictions, zero_division=0),
            u.ascii.MAGENTA,
        )

        u.ascii.puts("Confusion Matrix:", u.ascii.MAGENTA)
        u.ascii.puts(str(confusion_matrix(y_test, y_predictions)), u.ascii.MAGENTA)

        if hasattr(model, "feature_importances_"):
            importance = model.feature_importances_
            importance_df = pd.DataFrame(
                {
                    "feature": self.feature_columns,
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

            os.makedirs("tmp", exist_ok=True)

            plt.savefig(
                f"tmp/{self.symbol}_feature_importance.png",
                dpi=300,
                bbox_inches="tight",
            )

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts("🎉 Finished evaluating model", u.ascii.GREEN, print_end="")
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

    def _greedy_backward_feature_elimination(self):
        u.ascii.puts("=" * 60, u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "🔬 Starting Greedy Backward Elimination", u.ascii.CYAN, print_end=""
        )
        u.ascii.puts("=" * 60, u.ascii.CYAN)

        all_features = (
            self.feature_loader.columns
            + self.regime_history_feature_extractor.get_feature_names()
        )

        excluded_features = []

        # TODO: Temporary additional exclusion. Delete late.
        excluded_features.extend(
            [
                "ratio_ranging_last_5",
                "warm_up_body_to_lower_wick_ratio",
                "warm_up_body_to_upper_wick_ratio",
                "warm_up_body_to_wick_ratio",
            ]
        )
        remaining_features = all_features.copy()

        baseline_performance = self._evaluate_feature_subset(exclude=[])[
            "confidence_weighted"
        ]
        best_performance = baseline_performance

        u.ascii.puts(f"\nBaseline (All {len(all_features)} Features):", u.ascii.YELLOW)
        u.ascii.puts(
            f"  Confidence-Weighted P/L: {baseline_performance:.2f}%", u.ascii.YELLOW
        )

        elimination_log = []
        iteration = 0
        max_iterations = len(all_features)

        while iteration < max_iterations and len(remaining_features) > 0:
            iteration += 1

            u.ascii.puts(f"\n{'='*60}", u.ascii.CYAN, print_end="")
            u.ascii.puts(
                f"Round {iteration}: Testing {len(remaining_features)} features",
                u.ascii.CYAN,
                print_end="",
            )
            u.ascii.puts(f"{'='*60}", u.ascii.CYAN)

            results = {}

            for i, feature in enumerate(remaining_features, 1):
                test_exclude = excluded_features + [feature]

                u.ascii.puts(
                    f"[{i}/{len(remaining_features)}] Testing exclusion of: {feature}",
                    u.ascii.YELLOW,
                )

                performance = self._evaluate_feature_subset(exclude=test_exclude)[
                    "confidence_weighted"
                ]
                results[feature] = performance

            best_feature_to_exclude = max(results, key=results.get)
            best_round_performance = results[best_feature_to_exclude]

            improvement = best_round_performance - best_performance

            # TODO: Maybe do just <, not <=
            if best_round_performance <= best_performance:
                u.ascii.puts(
                    f"\n🛑  No improvement in Round {iteration}. Stopping elimination.",
                    u.ascii.YELLOW,
                )
                break

            excluded_features.append(best_feature_to_exclude)
            remaining_features.remove(best_feature_to_exclude)
            best_performance = best_round_performance

            elimination_log.append(
                {
                    "excluded_feature": best_feature_to_exclude,
                    "improvement": improvement,
                    "performance": best_round_performance,
                    "remaining_features": len(remaining_features),
                    "round": iteration,
                }
            )

            u.ascii.puts(
                f"\n Permanently excluded: {best_feature_to_exclude}", u.ascii.GREEN
            )
            u.ascii.puts(
                f"Remaining Features: {len(remaining_features)}", u.ascii.GREEN
            )
            u.ascii.puts(
                f"New Best Performance: {best_performance:.2f}%", u.ascii.GREEN
            )

        u.ascii.puts(f"\n{'='*60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "🎉 Greedy Backward Elimination Complete", u.ascii.CYAN, print_end=""
        )
        u.ascii.puts(f"{'='*60}", u.ascii.CYAN)

        u.ascii.puts(f"\nTotal Rounds: {iteration}", u.ascii.YELLOW)
        u.ascii.puts(f"Features Excluded: {len(excluded_features)}", u.ascii.YELLOW)
        u.ascii.puts(f"Features Remaining: {len(remaining_features)}", u.ascii.YELLOW)
        u.ascii.puts(f"Final Performance: {best_performance:.2f}%", u.ascii.YELLOW)
        u.ascii.puts(
            f"Total Improvement: {best_performance - baseline_performance:+.2f}%",
            u.ascii.YELLOW,
        )

        u.ascii.puts("\nElimination Sequence:", u.ascii.MAGENTA)

        for log_entry in elimination_log:
            u.ascii.puts(
                (
                    f"  Round {log_entry['round']}: "
                    f"Excluded '{log_entry['excluded_feature']}' → "
                    f"{log_entry['performance']:.2f}% "
                    f"({log_entry['improvement']:+.2f}%)"
                ),
                u.ascii.MAGENTA,
            )

        u.ascii.puts("\nOptimal Feature Subset:", u.ascii.GREEN)

        for feature in remaining_features:
            u.ascii.puts(f"• {feature}", u.ascii.GREEN)

        u.ascii.puts("\nTo use this subset, set:", u.ascii.CYAN)
        u.ascii.puts(f"exclude={excluded_features}", u.ascii.CYAN)

        out = {
            "baseline_performance": baseline_performance,
            "elimination_log": elimination_log,
            "excluded_features": excluded_features,
            "final_performance": best_performance,
            "improvement": best_performance - baseline_performance,
            "remaining_features": remaining_features,
        }

        current_dir = Path(__file__).resolve().parent
        save_dir = os.path.join(current_dir, "feature_selection")
        os.makedirs(save_dir, exist_ok=True)

        save_path = os.path.join(
            save_dir, f"greedy_backward_feature_elimination_{self.symbol}.json"
        )

        with open(save_path, "w") as f:
            json.dump(out, f, indent=2, default=str)

        return out

    def _merge_features_and_labels(self):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Merging features and labels into training data.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        self.features = pd.merge(
            self.features,
            self.regime_history_features,
            how="inner",
            on="market_session_id",
        )

        self.training_data = pd.merge(
            self.features,
            self.labels,
            how="inner",
            on="market_session_id",
        )

        self.training_data = self.training_data.sort_values(
            "market_session_opened_at", ascending=True
        )

        self.training_data = self.training_data.reset_index(drop=True)

        u.ascii.puts(self.training_data[:10].to_string(), u.ascii.YELLOW)
        u.ascii.puts("...", u.ascii.YELLOW)
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉 Finished merging features and labels into training data.",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

    def _prepare_data(self, exclude=None):
        if exclude is None:
            exclude = []

        u.ascii.puts("💡  Prepare data for model.", u.ascii.CYAN)

        target_column = "reverse_percentile_id"

        self._set_feature_columns(exclude=exclude)
        self.X = self.training_data[self.feature_columns]
        self.y = self.training_data[target_column]

        self._set_confidence_scores()

        unique_labels = sorted(self.y.unique())

        self.label_mapping = {label: idx for idx, label in enumerate(unique_labels)}
        self.reverse_label_mapping = {
            idx: label for label, idx in self.label_mapping.items()
        }

        self.y_class_mapped = self.y.map(self.label_mapping)

        X_train, X_temp, y_train, y_temp, confidence_train, confidence_temp = (
            train_test_split(
                self.X,
                self.y_class_mapped,
                self.confidence_scores,
                random_state=42,
                shuffle=False,  # Don't shuffle time series!
                test_size=0.3,
            )
        )

        self.X_train = X_train
        self.confidence_train = confidence_train
        self.y_train = y_train

        X_val, X_test, y_val, y_test, confidence_val, confidence_test = (
            train_test_split(
                X_temp,
                y_temp,
                confidence_temp,
                random_state=42,
                shuffle=False,
                test_size=0.5,  # 0.5 of 0.3 = 0.15 each
            )
        )

        self.X_test = X_test
        self.X_val = X_val
        self.confidence_test = confidence_test
        self.confidence_val = confidence_val
        self.y_test = y_test
        self.y_val = y_val

        u.ascii.puts(f"Features Columns: {self.feature_columns}", u.ascii.MAGENTA)
        u.ascii.puts(f"X: {self.X.shape[0]} samples", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"Training Set: {self.X_train.shape[0]} samples",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Validation Set: {self.X_val.shape[0]} samples",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(f"Test Set: {self.X_test.shape[0]} samples", u.ascii.MAGENTA)

        u.ascii.puts(
            f"Y Train Class Distribution:\n{self.y_train.value_counts(normalize=True)}",
            u.ascii.MAGENTA,
        )

    def _save_model(self, model):
        u.ascii.puts("💡  Saving model.", u.ascii.CYAN)

        ml_dir = Path(__file__).resolve().parent.parent.parent
        save_dir = os.path.join(ml_dir, "models", self.symbol)
        os.makedirs(save_dir, exist_ok=True)

        save_path = os.path.join(save_dir, "trade_setup_xgboost_model.json")
        model.save_model(save_path)

        u.ascii.puts(f"🎉 Model saved as {save_path}.", u.ascii.GREEN)

    def _set_class_weights(self):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts("💡  Setting class weights.", u.ascii.CYAN, print_end="")
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        classes = np.unique(self.y_train)
        class_weights = compute_class_weight(
            "balanced",
            classes=classes,
            y=self.y_train,
        )

        self.class_weight_dict = dict(zip(classes, class_weights))

        u.ascii.puts("Class Weights:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(f"{self.class_weight_dict}", u.ascii.MAGENTA)

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(f"🎉 Finished setting class weights.", u.ascii.GREEN, print_end="")
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

    def _set_confidence_scores(self):
        self.confidence_scores = self.training_data["confidence"].values

        u.ascii.puts(f"Confidence Score Statistics:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"  Mean: {self.confidence_scores.mean():.3f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Std: {self.confidence_scores.std():.3f}", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(
            f"  Min: {self.confidence_scores.min():.3f}", u.ascii.MAGENTA, print_end=""
        )
        u.ascii.puts(f"  Max: {self.confidence_scores.max():.3f}", u.ascii.MAGENTA)

    def _set_feature_columns(self, exclude=None):
        if exclude is None:
            exclude = []

        self.feature_columns = (
            self.feature_loader.columns
            + self.regime_history_feature_extractor.get_feature_names()
        )

        self.feature_columns = [
            col for col in self.feature_columns if col not in exclude
        ]

    def _time_series_validation(self, n_splits=5):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Using TimeSeriesSplit for temporal validation.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

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
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉 Finished time series cross validation.", u.ascii.GREEN, print_end=""
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

    def _train_class_weighted_model(self):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Training class-weighted XGBClassifier model.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        model_class = WeightedModel()

        self._set_class_weights()

        sample_weights = np.array(
            [self.class_weight_dict[label] for label in self.y_train]
        )

        model_class.train(
            X_train=self.X_train,
            X_val=self.X_val,
            sample_weights=sample_weights,
            y_train=self.y_train,
            y_val=self.y_val,
        )

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉 Finished training class-weighted XGBClassifier model.",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

        return model_class

    def _train_confidence_weighted_model(self):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Training confidence-weighted XGBClassifier model.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        model_class = WeightedModel()

        sample_weights = np.array(self.confidence_train)
        sample_weights = sample_weights / sample_weights.mean()

        model_class.train(
            X_train=self.X_train,
            X_val=self.X_val,
            sample_weights=sample_weights,
            y_train=self.y_train,
            y_val=self.y_val,
        )

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉 Finished training confidence-weighted XGBClassifier model.",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

        return model_class
