from sklearn.metrics import classification_report, confusion_matrix
from sklearn.model_selection import TimeSeriesSplit
from tabulate import tabulate
import ml.utils as u
import numpy as np
import pandas as pd
import xgboost as xgb


class Trainer:
    def __init__(self, training_data_builder, excluded_features=None):
        self.excluded_features = excluded_features if excluded_features else []
        self.model = None
        self.n_splits = 5
        self.training_data_builder = training_data_builder

        self.params = {
            "colsample_bytree": 0.8,
            "eval_metric": "mlogloss",  # Multi-class log loss
            "learning_rate": 0.1,
            "max_depth": 3,
            "min_child_weight": 5,
            "num_class": self.training_data_builder.num_class,
            "objective": "multi:softprob",  # Multi-class classification
            "random_state": 42,
            "subsample": 0.8,
            "tree_method": "hist",
            "verbosity": 0,
        }

        self.raw_labels = self.training_data_builder.raw_labels.copy()

    def train_with_cv(self, use_confidence_weighting=True):
        u.ascii.puts("=" * 60, u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "🎯 Training Multi-Class Model with CV", u.ascii.CYAN, print_end=""
        )
        u.ascii.puts("=" * 60, u.ascii.CYAN)

        feature_names = self._included_features()
        training_data = self.training_data_builder.training_data

        X = training_data[feature_names].values
        y = training_data["y"].values
        weights = (
            training_data["confidence"].values if use_confidence_weighting else None
        )

        cv_scores = []
        fold_predictions = []
        time_series_cv = TimeSeriesSplit(n_splits=self.n_splits)

        for fold_idx, (train_idx, val_idx) in enumerate(time_series_cv.split(X)):
            u.ascii.puts(f"  Fold {fold_idx + 1}/{self.n_splits}", u.ascii.YELLOW)

            X_train, X_val = X[train_idx], X[val_idx]
            y_train, y_val = y[train_idx], y[val_idx]

            train_dates = training_data.iloc[train_idx]["market_session_opened_at"]
            val_dates = training_data.iloc[val_idx]["market_session_opened_at"]

            train_start = train_dates.min()
            train_end = train_dates.max()
            val_start = val_dates.min()
            val_end = val_dates.max()

            u.ascii.puts(
                f"    Train period: {train_start} to {train_end}",
                u.ascii.YELLOW,
                print_end="",
            )
            u.ascii.puts(f"    Val period:   {val_start} to {val_end}", u.ascii.YELLOW)

            if use_confidence_weighting:
                weights_train = weights[train_idx]
            else:
                weights_train = None

            dtrain = xgb.DMatrix(
                X_train,
                feature_names=feature_names,
                label=y_train,
                weight=weights_train,
            )
            dval = xgb.DMatrix(X_val, feature_names=feature_names, label=y_val)

            model = xgb.train(
                self.params,
                dtrain,
                early_stopping_rounds=10,
                evals=[(dtrain, "train"), (dval, "val")],
                num_boost_round=100,
                verbose_eval=False,
            )

            val_probs = model.predict(dval)
            val_pred = np.argmax(val_probs, axis=1)

            val_data = training_data.iloc[val_idx].copy()
            val_data["predicted_class"] = val_pred
            val_data["predicted_trade_setup_id"] = val_data["predicted_class"].map(
                self.training_data_builder.reverse_label_mapping
            )

            accuracy = (val_pred == y_val).mean()
            mean_confidence = val_probs[np.arange(len(val_pred)), val_pred].mean()
            trading_metrics = self._calculate_trading_metrics(val_data)

            cv_scores.append(
                {
                    "fold": fold_idx + 1,
                    "accuracy": accuracy,
                    "train_start": train_start,
                    "train_end": train_end,
                    "val_start": val_start,
                    "val_end": val_end,
                    "total_optimal_profit_loss": trading_metrics[
                        "total_optimal_profit_loss"
                    ],
                    "total_predicted_profit_loss": trading_metrics[
                        "total_predicted_profit_loss"
                    ],
                    "profit_loss_capture": trading_metrics["profit_loss_capture"],
                    "mean_confidence": mean_confidence,
                    "sharpe_ratio": trading_metrics["sharpe_ratio"],
                    "train_size": len(train_idx),
                    "val_size": len(val_idx),
                }
            )

            fold_predictions.append(val_data)

            u.ascii.puts(f"    Accuracy: {accuracy:.1%}", u.ascii.GREEN, print_end="")

            u.ascii.puts("    Classification Report:", u.ascii.GREEN, print_end="")
            u.ascii.puts(
                classification_report(y_val, val_pred, zero_division=0),
                u.ascii.GREEN,
            )

            u.ascii.puts("    Confusion Matrix:", u.ascii.GREEN, print_end="")
            u.ascii.puts(
                str(confusion_matrix(y_val, val_pred)),
                u.ascii.GREEN,
            )

            u.ascii.puts(
                f"    Mean Confidence: {mean_confidence:.3f}",
                u.ascii.GREEN,
                print_end="",
            )

            u.ascii.puts(
                f"    Profit Loss Capture: {trading_metrics['profit_loss_capture']:+.1%}",
                u.ascii.GREEN,
                print_end="",
            )

            u.ascii.puts(
                f"    Total Optimal Profit Loss: ${trading_metrics['total_optimal_profit_loss']:,.2f}",
                u.ascii.GREEN,
                print_end="",
            )

            u.ascii.puts(
                f"    Total Predicted Profit Loss: ${trading_metrics['total_predicted_profit_loss']:,.2f}",
                u.ascii.GREEN,
                print_end="",
            )

            self._print_feature_importance(importance_type="gain", model=model)

        u.ascii.puts("=" * 60, u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "🎉 Finished training Multi-Class Model with CV", u.ascii.CYAN, print_end=""
        )
        u.ascii.puts("=" * 60, u.ascii.CYAN)

        cv = pd.DataFrame(cv_scores)
        all_predictions = pd.concat(fold_predictions, ignore_index=True)

        self._print_cv_summary(cv)

        return {"all_predictions": all_predictions, "cv": cv}

    def train_final_model(self, use_confidence_weighting=True):
        u.ascii.puts("=" * 60, u.ascii.CYAN, print_end="")
        u.ascii.puts("🎓 Training final model on all data", u.ascii.CYAN)
        u.ascii.puts("=" * 60, u.ascii.CYAN)

        feature_names = self._included_features()
        training_data = self.training_data_builder.training_data

        X = training_data[feature_names].values
        y = training_data["y"].values
        weights = (
            training_data["confidence"].values if use_confidence_weighting else None
        )

        dtrain = xgb.DMatrix(
            X,
            feature_names=feature_names,
            label=y,
            weight=weights,
        )

        self.model = xgb.train(
            self.params,
            dtrain,
            evals=[(dtrain, "train")],
            num_boost_round=100,
            verbose_eval=False,
        )

        train_probs = self.model.predict(dtrain)
        train_pred = np.argmax(train_probs, axis=1)
        train_accuracy = (train_pred == y).mean()

        u.ascii.puts(f"✅ Training Accuracy: {train_accuracy:.1%}", u.ascii.GREEN)

        u.ascii.puts("=" * 60, u.ascii.GREEN, print_end="")
        u.ascii.puts("🎓 Finished training final model on all data", u.ascii.GREEN)
        u.ascii.puts("=" * 60, u.ascii.GREEN)

        return self.model

    def _calculate_trading_metrics(self, predictions):
        market_session_results = []
        optimal_profit_losses = []
        predicted_profit_losses = []

        for market_session_id in predictions["market_session_id"].unique():
            pred_row = predictions[
                predictions["market_session_id"] == market_session_id
            ].iloc[0]

            predicted_trade_setup_id = pred_row["predicted_trade_setup_id"]

            market_session_labels = self.raw_labels[
                self.raw_labels["market_session_id"] == market_session_id
            ]

            if len(market_session_labels) == 0:
                continue

            predicted_rows = market_session_labels[
                market_session_labels["trade_setup_id"] == predicted_trade_setup_id
            ]

            if len(predicted_rows) == 0:
                # Predicted a trade_setup that doesn't exist for this session (shouldn't happen)
                continue

            optimal_profit_loss = market_session_labels["profit_loss_percent"].max()
            predicted_profit_loss = predicted_rows["profit_loss_percent"].iloc[0]

            predicted_profit_losses.append(predicted_profit_loss)
            optimal_profit_losses.append(optimal_profit_loss)

            market_session_results.append(
                {
                    "market_session_id": market_session_id,
                    "optimal_profit_loss": optimal_profit_loss,
                    "predicted_profit_loss": predicted_profit_loss,
                    "profit_loss_capture": (
                        predicted_profit_loss / optimal_profit_loss
                        if optimal_profit_loss != 0
                        else 0
                    ),
                }
            )

        total_optimal_profit_loss = sum(optimal_profit_losses)
        total_predicted_profit_loss = sum(predicted_profit_losses)

        if total_optimal_profit_loss != 0:
            profit_loss_capture = (
                total_predicted_profit_loss / total_optimal_profit_loss
            )
        else:
            profit_loss_capture = 0

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

        results = pd.DataFrame(market_session_results)

        return {
            "profit_loss_capture": profit_loss_capture,
            "sharpe_ratio": sharpe_predicted,
            "total_optimal_profit_loss": results["optimal_profit_loss"].sum(),
            "total_predicted_profit_loss": results["predicted_profit_loss"].sum(),
        }

    def _get_feature_importance(self, importance_type="gain", model=None):
        if model is None:
            u.ascii.puts("❌ Model can't bbe blank!", u.ascii.RED)
            return pd.DataFrame()

        importance_dict = model.get_score(importance_type=importance_type)

        importance = pd.DataFrame(
            [
                {"feature": feature, "importance": score}
                for feature, score in importance_dict.items()
            ]
        ).sort_values("importance", ascending=False)

        return importance

    def _included_features(self):
        return [
            f
            for f in self.training_data_builder.feature_columns
            if f not in self.excluded_features
        ]

    def _print_cv_summary(self, cv):
        u.ascii.puts("=" * 60, u.ascii.CYAN, print_end="")
        u.ascii.puts("📊 Cross-Validation Summary", u.ascii.CYAN, print_end="")
        u.ascii.puts("=" * 60, u.ascii.CYAN)

        u.ascii.puts("Per-Fold Results:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            tabulate(cv, headers="keys", tablefmt="psql", showindex=False),
            u.ascii.MAGENTA,
        )

        u.ascii.puts("-" * 60, u.ascii.CYAN, print_end="")
        u.ascii.puts("Aggregate Statistics:", u.ascii.MAGENTA, print_end="")
        u.ascii.puts(
            f"  Mean Accuracy:     {cv['accuracy'].mean():.1%} (±{cv['accuracy'].std():.1%})",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Optimal Strategy Return: ${cv['total_optimal_profit_loss'].sum():,.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"Model Strategy Return: ${cv['total_predicted_profit_loss'].sum():,.2f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Mean Profit Loss Capture:  {cv['profit_loss_capture'].mean():+.1%} (±{cv['profit_loss_capture'].std():.1%})",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Mean Confidence:   {cv['mean_confidence'].mean():.3f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts(
            f"  Mean Sharpe Ratio:  {cv['sharpe_ratio'].mean():.3f}",
            u.ascii.MAGENTA,
            print_end="",
        )
        u.ascii.puts("-" * 60, u.ascii.CYAN)

    def _print_feature_importance(self, importance_type="gain", model=None, top_n=None):
        importance = self._get_feature_importance(
            importance_type=importance_type,
            model=model,
        )

        if importance.empty:
            return

        top_n = top_n if top_n else len(importance)

        u.ascii.puts("=" * 60, u.ascii.CYAN, print_end="")
        u.ascii.puts(
            f"\n📊 Top {top_n} Most Important Features ({importance_type}):",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts("=" * 60, u.ascii.CYAN)

        top_features = importance.head(top_n).copy()

        top_features["importance_pct"] = (
            top_features["importance"] / top_features["importance"].sum() * 100
        )

        display = top_features.copy()
        display["importance"] = display["importance"].round(1)
        display["importance_pct"] = display["importance_pct"].apply(
            lambda x: f"{x:.1f}%"
        )

        u.ascii.puts(
            tabulate(display, headers="keys", tablefmt="psql", showindex=False),
            u.ascii.MAGENTA,
        )

        return importance
