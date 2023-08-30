from ml.utils import ascii


class InputLoader:
    def __init__(self, symbol: str):
        self.symbol = symbol

    def load(self):
        ascii.puts(f"💿 Loading input data for {ascii.CYAN}{self.symbol}", ascii.YELLOW)
