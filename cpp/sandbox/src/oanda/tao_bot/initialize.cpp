#ifndef OANDA__TAO_BOT_initialize
#define OANDA__TAO_BOT_initialize

#include "build_performance.cpp"     // build_performance
#include "fetch_account_balance.cpp" // fetch_account_balance
#include "fetch_quote.cpp"           // fetch_quote
#include "lib/formatted.cpp"         // Formatted::error_message
#include "lib/utils/boolean.cpp"     // ::utils::boolean
#include "load_performance.cpp"      // load_performance
#include "set_trade_direction.cpp"   // set_trade_direction
#include "spread_limit.cpp"          // spread_limit
#include "tao_bot.h"                 // Oanda::TaoBot, quantity, symbol
#include <locale.h>                  // setlocale
#include <map>                       // std::map
#include <stdexcept>                 // std::invalid_argument
#include <string>                    // std::map

void Oanda::TaoBot::initialize(char *symbol_,
                               std::map<std::string, std::string> &flags) {
  if (symbol_ == nullptr) {
    std::string message =
        Formatted::error_message("Must provide a currency pair");
    throw std::invalid_argument(message);
  }

  this->symbol = symbol_;

  if (spread_limit() <= 0) {
    std::string message = Formatted::error_message(
        "Must specify a spread limit for <" + std::string(symbol_) + ">");
    throw std::invalid_argument(message);
  }

  // Support comma separation in print output
  setlocale(LC_NUMERIC, "");

  this->account_balance = this->original_account_balance =
      fetch_account_balance();

  fetch_quote();
  load_performance();
  set_trade_direction();

  this->performance = build_performance();
}

#endif
