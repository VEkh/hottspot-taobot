import ml.utils as u
import numpy as np
import pandas as pd
import xgboost as xgb


class WeightedModel:
    def __init__(self):
        self.model = None
        self.predictions = pd.DataFrame()

    def predict(self, X):
        if self.model is None:
            u.ascii.puts(
                "！ WeightedModel failed to predict because model is empty",
                u.ascii.RED,
            )

            return

        self.predictions = self.model.predict(X)

        return self.predictions

    def train(
        self,
        X_train=None,
        X_val=None,
        sample_weights=None,
        y_train=None,
        y_val=None,
    ):
        if X_train is None:
            X_train = pd.DataFrame()
        if X_val is None:
            X_val = pd.DataFrame()
        if y_train is None:
            y_train = pd.DataFrame()
        if y_val is None:
            y_val = pd.DataFrame()

        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Training weighted XGBClassifier model.",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        self.model = xgb.XGBClassifier(
            colsample_bytree=0.8,
            early_stopping_rounds=50,
            eval_metric=["logloss", "error"],
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

        self.model.fit(
            X_train,
            y_train,
            eval_set=[(X_val, y_val)],
            sample_weight=sample_weights,
            verbose=True,
        )

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉 Finished training weighted XGBClassifier model.",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)
