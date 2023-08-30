from .input_loader import InputLoader
from argparse import ArgumentParser
from ml.utils import ascii


def run(args: ArgumentParser):
    ascii.puts("🤖 Training five minute prediction model", ascii.YELLOW)

    loader = InputLoader(args.symbol)
    loader.load()
