from argparse import ArgumentParser

usage = """
        main.h {predict} symbol [--env] [--market-session-id]
        main.h {train}   symbol [--env] [--market-session-duration-seconds] [--market-session-warm-up-duration-seconds]
"""

description = """
    Functions for training and using a model that predicts which trade setup to
    use for a given market session.
"""

arg_parser = ArgumentParser(
    description=description,
    usage=usage,
)

cmd_help = """
    Commands to run: predict [trade setup];  train [the model]
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
    choices=["backtest", "development", "production"],
    default="development",
    dest="env",
    help="Database environment",
)

arg_parser.add_argument(
    "--market-session-duration-seconds",
    "-d",
    default=0,
    dest="market_session_duration_seconds",
    help="Duration of the market sessions",
)

arg_parser.add_argument(
    "--market-session-warm-up-duration-seconds",
    "-w",
    default=0,
    dest="market_session_warm_up_duration_seconds",
    help="Duration of the market sessions' warm up period",
)

args = arg_parser.parse_args()
args.symbol = args.symbol.upper()


match args.command:
    case "train":
        from ml.db import Conn
        from train import Train

        conn = Conn(args.env)
        conn.connect()

        trainer = Train(
            db_conn=conn,
            market_session_duration_seconds=args.market_session_duration_seconds,
            market_session_warm_up_duration_seconds=args.market_session_warm_up_duration_seconds,
            symbol=args.symbol,
        )

        trainer.run()

        conn.disconnect()
