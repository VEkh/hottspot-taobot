from argparse import ArgumentParser

arg_parser = ArgumentParser(
    description="Functions for training and using a model that predicts the next five minutes of price change.",
    usage="main.h {train} symbol [--env]",
)
arg_parser.add_argument(
    "command",
    choices=["train"],
    help="Command to run (train: Train the model)",
)
arg_parser.add_argument(
    "symbol",
    help="Symbol of model's instrument (e.g. AMZN)",
)
arg_parser.add_argument(
    "--env",
    "-e",
    choices=["development", "production"],
    default="development",
    dest="env",
    help="Database environment",
)

args = arg_parser.parse_args()
args.symbol = args.symbol.upper()

match args.command:
    case "train":
        import train

        train.run(args)
