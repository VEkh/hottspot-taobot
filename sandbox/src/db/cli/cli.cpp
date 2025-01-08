#ifndef DB__CLI
#define DB__CLI

#include "cli.h" // BaseCli, DB::Cli

// Overrides
#include "execute.cpp"

DB::Cli::Cli(int c, char **v) : BaseCli(c, v) {
  this->cli_name = "DB";

  this->commands = {
      {"build_candles                          <SYMBOL> <OPTS>               "
       "  ",
       "Build five minute candles for the given symbol"},
      {"import_historical_quotes               <SYMBOL> --api=<API_NAME> "
       "<OPTS>",
       "Import symbol's historical quotes"},
      {"log_snapshots                          --api=<API_NAME> <FLAGS>      "
       "  ",
       "Print daily account performance for the given api key"},
      {"net_return                             <SYMBOL> <OPTS>               "
       "  ",
       "Compute symbol's net return"},
  };
};

#endif
