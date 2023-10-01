from argparse import ArgumentParser
import sys
import time

import ml.utils as u

usage = """
        main.h {predict} symbol [--duration-min] [--env] [--ref-epoch] [--timestamps]
        main.h {train}   symbol [--duration-min] [--env]
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
    "--duration-min",
    "-dm",
    dest="duration_minutes",
    help="Duration minutes",
    required=True,
)

arg_parser.add_argument(
    "--env",
    "-e",
    choices=["backtest", "development", "production"],
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

timestamps_help = u.string.strip_heredoc(
    f"""
    Time to be written to database timestamp columns (inserted_at, updated_at)
    (e.g. 'now()', to_timestamp({int(now)}), etc.)
    """
)

arg_parser.add_argument(
    "--timestamps",
    "-t",
    default=f"now()",
    dest="timestamps",
    help=timestamps_help,
)

args = arg_parser.parse_args()
args.duration_minutes = int(args.duration_minutes)
args.symbol = args.symbol.upper()

match args.command:
    case "predict":
        from ml.db import Conn
        from predict import Predict

        conn = Conn(args.env)
        conn.connect()
        conn.conn.autocommit = True

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
            duration_minutes=args.duration_minutes,
            ref_epoch=args.ref_epoch,
            symbol=args.symbol,
            timestamps=args.timestamps,
        )

        predictor.run()

        conn.disconnect()

    case "train":
        from ml.db import Conn
        from train import Train

        conn = Conn(args.env)
        conn.connect()

        trainer = Train(
            db_conn=conn,
            duration_minutes=args.duration_minutes,
            symbol=args.symbol,
        )

        trainer.run()

        conn.disconnect()
