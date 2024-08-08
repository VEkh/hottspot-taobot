#ifndef ALPACA__TAO_BOT_BACKTEST_fetch_asset
#define ALPACA__TAO_BOT_BACKTEST_fetch_asset

#include "backtest.h" // Alpaca::TaoBotBacktest
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::string

std::string Alpaca::TaoBotBacktest::fetch_asset() {
  const char *response = R"(
    {
      "easy_to_borrow": true,
      "shortable": true
    }
  )";

  return response;
}

#endif
