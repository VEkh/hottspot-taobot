from .feature_loader import FeatureLoader
from .label_builder import LabelBuilder
from .label_loader import LabelLoader
from .regime_history_feature_extractor import RegimeHistoryFeatureExtractor
from .volatility_feature_extractor import VolatilityFeatureExtractor
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
        self.volatility_features = pd.DataFrame()
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

        self.volatility_feature_extractor = VolatilityFeatureExtractor(
            atr_windows=[4, 8, 14, 26],
            percentile_window=100,
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
        self.label_loader.stop_profit_id = 2

        self.label_loader.load()
        self.labels = self.label_builder.build(self.label_loader.labels)
        # self.regime_history_features = (
        #     self.regime_history_feature_extractor.fit_transform(self.labels)
        # )
        self.volatility_features = self.volatility_feature_extractor.fit_transform(
            pd.merge(
                self.features,
                self.labels,
                how="inner",
                on="market_session_id",
            )
        )

        self._merge_features_and_labels()

        # feature_elimination_results = self._greedy_backward_feature_elimination()
        # self._evaluate_feature_subset(
        #     exclude=feature_elimination_results["excluded_features"]
        # )

        # Run 2
        # excluded_features = [
        #     "avg_true_range_26",
        #     "count_ranging_last_10",
        #     "ratio_ranging_last_3",
        #     "ratio_trending_last_3",
        #     "warm_up_body_to_upper_wick_ratio",
        #     "warm_up_body_to_wick_ratio",
        # ]
        # self._evaluate_feature_subset(exclude=excluded_features)

        self._evaluate_feature_subset()
        # self._save_model()

    def _analyze_cv_fold_conditions(self, fold_data=None, fold_idx=0):
        if fold_data is None:
            fold_data = pd.DataFrame()

        avg_atr = fold_data["avg_true_range_26"].mean()
        atr_std = fold_data["avg_true_range_26"].std()
        atr_75th = fold_data["avg_true_range_26"].quantile(0.75)

        fold_data["consecutive_same_regime"] = self._compute_consecutive_same_regime(
            fold_data["reverse_percentile_id"]
        )
        avg_consecutive = fold_data["consecutive_same_regime"].mean()
        max_consecutive = fold_data["consecutive_same_regime"].max()

        regime_switches = self._count_regime_changes(fold_data["reverse_percentile_id"])
        switch_rate = regime_switches / len(fold_data) if len(fold_data) > 0 else 0

        label_counts = fold_data["reverse_percentile_id"].value_counts()
        label_balance = (
            label_counts.min() / label_counts.max() if len(label_counts) > 1 else 1.0
        )

        start_date = fold_data["market_session_opened_at"].min()
        end_date = fold_data["market_session_opened_at"].max()

        avg_confidence = fold_data["confidence"].mean()

        return {
            "fold": fold_idx,
            "start_date": start_date,
            "end_date": end_date,
            "n_samples": len(fold_data),
            "atr_75th": atr_75th,
            "atr_std": atr_std,
            "avg_atr": avg_atr,
            "avg_confidence": avg_confidence,
            "avg_consecutive_regime": avg_consecutive,
            "label_balance": label_balance,
            "max_consecutive_regime": max_consecutive,
            "pct_ranging": (fold_data["reverse_percentile_id"] == 2).mean(),
            "pct_trending": (fold_data["reverse_percentile_id"] == 1).mean(),
            "regime_switches": regime_switches,
            "switch_rate": switch_rate,
        }

    # NOTE: Dead code
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
        profit_loss_capture = (total_return_predicted / total_return_actual) * 100

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

        return {
            "profit_loss_capture": profit_loss_capture,
            "sharpe_ratio": sharpe_predicted,
        }

    def _compute_consecutive_same_regime(self, label_series):
        consecutive_count = []
        current_count = 1

        for i in range(len(label_series)):
            if i == 0:
                consecutive_count.append(1)
            elif label_series.iloc[i] == label_series.iloc[i - 1]:
                current_count += 1
                consecutive_count.append(current_count)
            else:
                current_count = 1
                consecutive_count.append(1)

        return pd.Series(consecutive_count, index=label_series.index)

    def _count_regime_changes(self, label_series):
        switches = 0

        for i in range(1, len(label_series)):
            if label_series.iloc[i] != label_series.iloc[i - 1]:
                switches += 1

        return switches

    def _evaluate_feature_subset(self, exclude=None):
        if exclude is None:
            exclude = []

        self._prepare_data(exclude=exclude)
        profit_loss_data = self.training_data.iloc[self.X_test.index][
            ["profit_loss_percent_1", "profit_loss_percent_2"]
        ]

        class_weighted_model_class = self._train_class_weighted_model(
            X_train=self.X_train,
            X_val=self.X_val,
            y_train=self.y_train,
            y_val=self.y_val,
        )

        self._evaluate_model(
            X_test=self.X_test,
            model_class=class_weighted_model_class,
            y_test=self.y_test,
        )

        class_weighted_profit_loss_capture = self._calculate_trading_metrics(
            profit_loss_data=profit_loss_data,
            y_predictions=class_weighted_model_class.predictions,
            y_true=self.y_test,
        )["profit_loss_capture"]

        confidence_weighted_model_class = self._train_confidence_weighted_model(
            X_train=self.X_train,
            X_val=self.X_val,
            sample_weights=self.confidence_train,
            y_train=self.y_train,
            y_val=self.y_val,
        )

        self._evaluate_model(
            X_test=self.X_test,
            model_class=confidence_weighted_model_class,
            y_test=self.y_test,
        )

        confidence_weighted_profit_loss_capture = self._calculate_trading_metrics(
            profit_loss_data=profit_loss_data,
            y_predictions=confidence_weighted_model_class.predictions,
            y_true=self.y_test,
        )["profit_loss_capture"]

        self._time_series_validation(n_splits=5)

        return {
            "class_weighted": class_weighted_profit_loss_capture,
            "confidence_weighted": confidence_weighted_profit_loss_capture,
        }

    def _evaluate_model(
        self,
        X_test=None,
        y_test=None,
        model_class=None,
    ):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts("💡  Evaluating model", u.ascii.CYAN, print_end="")
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        if X_test is None:
            X_test = pd.DataFrame()

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

        if y_test is None:
            y_test = pd.DataFrame()

        y_predictions_display = model_class.predict(X_test)
        y_test_display = y_test

        if self.reverse_label_mapping:
            y_test_display = y_test.map(self.reverse_label_mapping)
            y_predictions_display = pd.Series(y_predictions_display).map(
                self.reverse_label_mapping
            )

        accuracy = accuracy_score(y_test_display, y_predictions_display)

        u.ascii.puts(f"Accuracy: {accuracy:.4f}", u.ascii.MAGENTA)

        u.ascii.puts("Classification Report:", u.ascii.MAGENTA)
        u.ascii.puts(
            classification_report(
                y_test_display, y_predictions_display, zero_division=0
            ),
            u.ascii.MAGENTA,
        )

        u.ascii.puts("Confusion Matrix:", u.ascii.MAGENTA)
        u.ascii.puts(
            str(confusion_matrix(y_test_display, y_predictions_display)),
            u.ascii.MAGENTA,
        )

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

        return accuracy

    def _get_class_weights(self, y_train=None):
        if y_train is None:
            y_train = pd.DataFrame()

        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts("💡  Setting class weights.", u.ascii.CYAN, print_end="")
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        classes = np.unique(y_train)
        class_weights = compute_class_weight(
            "balanced",
            classes=classes,
            y=y_train,
        )

        class_weight_dict = dict(zip(classes, class_weights))

        u.ascii.puts("Class Weights:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(f"{class_weight_dict}", u.ascii.MAGENTA)

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(f"🎉 Finished setting class weights.", u.ascii.GREEN, print_end="")
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

        return class_weight_dict

    def _greedy_backward_feature_elimination(self):
        u.ascii.puts("=" * 60, u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "🔬 Starting Greedy Backward Elimination", u.ascii.CYAN, print_end=""
        )
        u.ascii.puts("=" * 60, u.ascii.CYAN)

        # NOTE: Feature Modify
        all_features = (
            self.feature_loader.columns
            # + self.regime_history_feature_extractor.get_feature_names()
            + self.volatility_feature_extractor.get_feature_names()
        )

        excluded_features = []

        # TODO: Initial exclusion for greedy elimination. Delete later.
        # excluded_features.extend(
        #     [
        #         "avg_true_range_26",
        #         "count_ranging_last_10",
        #         "ratio_ranging_last_3",
        #         "ratio_trending_last_3",
        #         "warm_up_body_to_upper_wick_ratio",
        #         "warm_up_body_to_wick_ratio",
        #     ]
        # )
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

        # NOTE: Feature Modify
        # self.features = pd.merge(
        #     self.features,
        #     self.regime_history_features,
        #     how="inner",
        #     on="market_session_id",
        # )

        self.features = pd.merge(
            self.features,
            self.volatility_features,
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

        # NOTE: Feature Modify
        self.feature_columns = (
            self.feature_loader.columns
            # + self.regime_history_feature_extractor.get_feature_names()
            + self.volatility_feature_extractor.get_feature_names()
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

        fold_conditions = []
        results = []
        time_series_cv = TimeSeriesSplit(n_splits)

        for fold, (train_idx, val_idx) in enumerate(time_series_cv.split(self.X), 1):
            X_train_cv, X_val_cv = self.X.iloc[train_idx], self.X.iloc[val_idx]
            y_train_cv, y_val_cv = (
                self.y_class_mapped.iloc[train_idx],
                self.y_class_mapped.iloc[val_idx],
            )

            sample_weights_cv = self.confidence_scores[train_idx]

            model_class = self._train_confidence_weighted_model(
                X_train=X_train_cv,
                X_val=X_val_cv,
                sample_weights=sample_weights_cv,
                y_train=y_train_cv,
                y_val=y_val_cv,
            )

            accuracy = self._evaluate_model(
                X_test=X_val_cv,
                model_class=model_class,
                y_test=y_val_cv,
            )

            profit_loss_data = self.training_data.iloc[val_idx][
                ["profit_loss_percent_1", "profit_loss_percent_2"]
            ]

            trade_performance = self._calculate_trading_metrics(
                profit_loss_data=profit_loss_data,
                y_predictions=model_class.predictions,
                y_true=y_val_cv,
            )

            score = model_class.model.score(X_val_cv, y_val_cv)

            results.append(
                {
                    "accuracy": accuracy,
                    "fold": fold,
                    "profit_loss_capture": trade_performance["profit_loss_capture"],
                    "score": score,
                    "sharpe_ratio": trade_performance["sharpe_ratio"],
                    "train_size": len(train_idx),
                    "val_size": len(val_idx),
                }
            )

            val_fold_data = self.training_data.iloc[val_idx].copy()
            fold_condition = self._analyze_cv_fold_conditions(
                fold_idx=fold,
                fold_data=val_fold_data,
            )
            fold_condition["accuracy"] = accuracy
            fold_condition["profit_loss_capture"] = trade_performance[
                "profit_loss_capture"
            ]
            fold_condition["sharpe_ratio"] = trade_performance["sharpe_ratio"]
            fold_conditions.append(fold_condition)

        fold_conditions = pd.DataFrame(fold_conditions)
        results = pd.DataFrame(results)

        u.ascii.puts(
            f"Time Series Cross Validation Results:\n{results.to_string()}",
            u.ascii.MAGENTA,
        )

        u.ascii.puts(
            f"Mean Profit Loss Capture: {results['profit_loss_capture'].mean():.4f} (+/- {(results['profit_loss_capture'].std() * 2):.4f})",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Mean Score: {results['score'].mean():.4f} (+/- {(results['score'].std() * 2):.4f})",
            u.ascii.MAGENTA,
        )

        u.ascii.puts("Market Conditions By Fold", u.ascii.CYAN, print_end="")
        u.ascii.puts("-" * 60, u.ascii.CYAN, print_end="")
        u.ascii.puts(fold_conditions.to_string(), u.ascii.MAGENTA)

        u.ascii.puts("Condition-Performance Correlations", u.ascii.CYAN, print_end="")
        u.ascii.puts("-" * 60, u.ascii.CYAN)

        correlations = (
            fold_conditions[
                [
                    "avg_atr",
                    "switch_rate",
                    "label_balance",
                    "avg_consecutive_regime",
                    "profit_loss_capture",
                ]
            ]
            .corr()["profit_loss_capture"]
            .sort_values(ascending=False)
        )

        u.ascii.puts(f"Correlation with P/L Capture:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(correlations.to_string(), u.ascii.MAGENTA)

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉 Finished time series cross validation.", u.ascii.GREEN, print_end=""
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

    def _train_class_weighted_model(
        self,
        X_train=None,
        X_val=None,
        y_train=None,
        y_val=None,
    ):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Training class-weighted XGBClassifier model.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        if X_train is None:
            X_train = pd.DataFrame()

        if X_val is None:
            X_val = pd.DataFrame()

        if y_train is None:
            y_train = pd.DataFrame()

        if y_val is None:
            y_val = pd.DataFrame()

        model_class = WeightedModel()

        class_weight_dict = self._get_class_weights(y_train)
        sample_weights = np.array([class_weight_dict[label] for label in y_train])

        model_class.train(
            X_train=X_train,
            X_val=X_val,
            sample_weights=sample_weights,
            y_train=y_train,
            y_val=y_val,
        )

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉 Finished training class-weighted XGBClassifier model.",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

        return model_class

    def _train_confidence_weighted_model(
        self,
        X_train=None,
        X_val=None,
        sample_weights=None,
        y_train=None,
        y_val=None,
    ):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Training confidence-weighted XGBClassifier model.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        if X_train is None:
            X_train = pd.DataFrame()

        if X_val is None:
            X_val = pd.DataFrame()

        if sample_weights is None:
            sample_weights = pd.DataFrame()

        if y_train is None:
            y_train = pd.DataFrame()

        if y_val is None:
            y_val = pd.DataFrame()

        model_class = WeightedModel()

        sample_weights = np.array(sample_weights)
        sample_weights = sample_weights / sample_weights.mean()

        model_class.train(
            X_train=X_train,
            X_val=X_val,
            sample_weights=sample_weights,
            y_train=y_train,
            y_val=y_val,
        )

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉 Finished training confidence-weighted XGBClassifier model.",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

        return model_class
