from argparse import ArgumentParser
import sys
import time

import ml.utils as u

usage = """
        main.h {predict} symbol [--env] [--ref-epoch]
        main.h {train}   symbol [--env]
"""

arg_parser = ArgumentParser(
    description="Functions for training and using a model that predicts the next five minutes of price change.",
    usage=usage,
)

cmd_help = """
    Commands to run: predict [next five minutes];  train [the model]
"""

arg_parser.add_argument(
    "command",
    choices=["predict", "train"],
    help=cmd_help,
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

now = time.time()

arg_parser.add_argument(
    "--ref-epoch",
    "-r",
    default=f"{now}",
    dest="ref_epoch",
    help=f"Reference epoch from which a prediction will be made (e.g. {int(now)})",
)

args = arg_parser.parse_args()
args.symbol = args.symbol.upper()

match args.command:
    case "predict":
        from ml.db import Conn
        from predict import Predict

        conn = Conn(args.env)
        conn.connect()

        try:
            args.ref_epoch = float(args.ref_epoch)
        except ValueError:
            u.ascii.puts(
                "❗ Reference Epoch (-r, --ref-epoch) must be a float or integer. See help (-h)",
                u.ascii.RED,
            )

            sys.exit(1)

        predictor = Predict(
            db_conn=conn,
            ref_epoch=args.ref_epoch,
            symbol=args.symbol,
        )

        predictor.run()

        conn.disconnect()

    case "train":
        from ml.db import Conn
        from train import Train

        conn = Conn(args.env)
        conn.connect()

        trainer = Train(db_conn=conn, symbol=args.symbol)
        trainer.run()

        conn.disconnect()
