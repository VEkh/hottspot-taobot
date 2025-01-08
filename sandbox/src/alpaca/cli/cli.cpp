#ifndef ALPACA__CLI
#define ALPACA__CLI

#include "cli.h" // BaseCli, Alpaca::Cli

// Overrides
#include "execute.cpp"

Alpaca::Cli::Cli(int c, char **v) : BaseCli(c, v) {
  this->cli_name = "Alpaca";

  this->commands = {
      {"cancel_orders  <ORDER_IDS>         ", "Cancel outsanding orders"},
      {"fetch_asset    <SYMBOL>            ",
       "Get asset info for the given symbol"},
      {"fetch_quote    <SYMBOL>            ", "Get quote for the given symbol"},
      {"log_benchmark                      ",
       "Print cumulative return and compare to benchmark indexes"},
      {"quotes_stream  <SYMBOLS>           ",
       "Stream quotes for given symbol(s)"},
      {"quotes_watch   <SYMBOLS>           ",
       "Persist and make computations for fetched/streamed quotes"},
      {"stream_account                     ", "Stream account info"},
      {"tao_bot        <SYMBOL> <QUANTITY> ",
       "Launch trading bot for the given currency pair"},
  };
}

#endif
