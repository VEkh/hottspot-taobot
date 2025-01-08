#ifndef OANDA__CLI
#define OANDA__CLI

#include "cli.h" // BaseCli, Oanda::Cli

// Overrides
#include "execute.cpp"

Oanda::Cli::Cli(int c, char **v) : BaseCli(c, v) {
  this->cli_name = "Oanda";

  this->commands = {
      {"fetch_quote      <SYMBOL>                     ",
       "Get quote for the given symbol"},
      {"quotes_watch     <SYMBOLS>                    ",
       "Persist and make computations for fetched/streamed quotes"},
      {"stream_account                                ", "Stream account info"},
      {"tao_bot <SYMBOL> <QUANTITY>                   ",
       "Launch trading bot for the given currency pair"},
  };
}

#endif
