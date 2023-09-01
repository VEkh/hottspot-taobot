from .input_loader import InputLoader
from ml.utils import ascii


class Train:
    def __init__(self, db_conn=None, env="", symbol=""):
        self.db_conn = db_conn
        self.env = env
        self.symbol = symbol

    def run(self):
        ascii.puts("🤖 Training five minute prediction model", ascii.YELLOW)

        loader = InputLoader(db_conn=self.db_conn, symbol=self.symbol)
        inputs = loader.load()
