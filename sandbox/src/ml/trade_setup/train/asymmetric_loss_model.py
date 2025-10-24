import ml.utils as u
import numpy as np
import pandas as pd
import xgboost as xgb


class AsymmetricLossModel:
    def __init__(self, false_negative_weight=5.0):
        self.false_negative_weight = false_negative_weight
        self.model = None
        self.predictions = pd.DataFrame()

    def predict(self, X=pd.DataFrame(), probability_threshold=0.5):
        if self.model is None:
            u.ascii.puts(
                "！ AsymmetricLossModel failed to predict because model is empty",
                u.ascii.RED,
            )

            return

        dtest = xgb.DMatrix(X)
        predict_probabilities = self.model.predict(dtest)

        # Convert to probabilities
        predict_probabilities = 1.0 / (1.0 + np.exp(-predict_probabilities))

        self.predictions = (predict_probabilities >= probability_threshold).astype(int)

        return self.predictions

    def train(
        self,
        X_train=pd.DataFrame(),
        X_val=pd.DataFrame(),
        sample_weights=None,
        y_train=pd.DataFrame(),
        y_val=pd.DataFrame(),
    ):
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "💡  Training asymmetric loss XGBClassifier model",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.CYAN)

        dtrain = xgb.DMatrix(X_train, label=y_train, weight=sample_weights)
        dval = xgb.DMatrix(X_val, label=y_val)

        params = {
            "colsample_bytree": 0.8,
            "learning_rate": 0.05,  # Lower learning rate for custom objective
            "max_depth": 4,
            "min_child_weight": 3,
            "random_state": 42,
            "reg_alpha": 0.1,
            "reg_lambda": 1.0,
            "subsample": 0.8,
        }

        evals = [(dtrain, "train"), (dval, "eval")]

        self.model = xgb.train(
            dtrain=dtrain,
            early_stopping_rounds=50,
            evals=evals,
            num_boost_round=1000,
            obj=self.__asymmetric_logloss,
            params=params,
            verbose_eval=True,
        )

        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            "🎉  Finished training asymmetric loss XGBClassifier model",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(f"{'=' * 60}", u.ascii.GREEN)

        return self.model

    def __asymmetric_logloss(self, y_predictions, dtrain):
        """
        Custom loss function with asymmetric penalties.

        Heavily penalizes: Predicting rp_id=1 when truth is rp_id=2
        (This means using late reversal when early reversal was needed)
        """

        y_true = dtrain.get_label()
        p = 1.0 / (1.0 + np.exp(-y_predictions))

        grad = np.zeros_like(y_true)
        hess = np.zeros_like(y_true)

        for i in range(len(y_true)):
            # True label is class 1 (rp_id=2 mapped to 1)
            if y_true[i] == 1:
                # False negative: predicted 0 when truth is 1 - VERY BAD
                grad[i] = -self.false_negative_weight * (1 - p[i])
                hess[i] = self.false_negative_weight * p[i] * (1 - p[i])
            else:
                # True label is class 0 (rp_id=1 mapped to 0)
                # False positive: predicted 1 when truth is 0 - not as bad
                grad[i] = p[i]
                hess[i] = p[i] * (1 - p[i])

        return grad, hess
