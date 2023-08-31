from .input_loader import InputLoader
from ml.utils import ascii


class Train:
    def __init__(self, args):
        self.env = args.env
        self.symbol = args.symbol

    def run(self):
        ascii.puts("🤖 Training five minute prediction model", ascii.YELLOW)

        loader = InputLoader(self.symbol)
        loader.load()
