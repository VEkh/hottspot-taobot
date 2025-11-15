from .training_data_builder import TrainingData
from .trainer import Trainer
from pathlib import Path
from sklearn.metrics import classification_report, confusion_matrix
import json
import ml.utils as u
import os
import textwrap


class Train:
    def __init__(
        self,
        db_conn,
        market_session_duration_seconds,
        market_session_warm_up_duration_seconds,
        symbol,
    ):
        self.market_session_duration_seconds = market_session_duration_seconds
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.symbol = symbol

:       self.training_data_builder = TrainingData(
            db_conn=db_conn,
            market_session_duration_seconds=market_session_duration_seconds,
            market_session_warm_up_duration_seconds=market_session_warm_up_duration_seconds,
            symbol=symbol,
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

        self.training_data_builder.build()

        trainer = Trainer(self.training_data_builder)
        trainer.train_with_cv()
