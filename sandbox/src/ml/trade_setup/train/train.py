import ml.utils as u
from .input_loader import InputLoader
from .label_loader import LabelLoader


class Train:
    def __init__(
        self,
        db_conn=None,
        market_session_duration_seconds=0,
        market_session_warm_up_duration_seconds=0,
        symbol=None,
    ):
        self.db_conn = db_conn
        self.inputs = []
        self.market_session_duration_seconds = market_session_duration_seconds
        self.labels = []
        self.market_session_warm_up_duration_seconds = (
            market_session_warm_up_duration_seconds
        )
        self.symbol = symbol

        self.input_loader = InputLoader(
            db_conn=self.db_conn,
            market_session_duration_seconds=self.market_session_duration_seconds,
            market_session_warm_up_duration_seconds=self.market_session_warm_up_duration_seconds,
            symbol=self.symbol,
        )

        self.label_loader = LabelLoader(
            db_conn=self.db_conn,
            market_session_duration_seconds=self.market_session_duration_seconds,
            market_session_warm_up_duration_seconds=self.market_session_warm_up_duration_seconds,
            symbol=self.symbol,
        )

    def run(self):
        description = f"""
        🤖 Training model for predicting {u.ascii.CYAN}{self.symbol}{u.ascii.YELLOW} trade setups.

        ✅ Market Session Duration (Seconds): {self.market_session_duration_seconds}
        ✅ Market Session Warm Up Duration (Seconds): {self.market_session_warm_up_duration_seconds}
        """

        u.ascii.puts(description, u.ascii.YELLOW)

        self.inputs = self.input_loader.load()
        self.labels = self.label_loader.load()
