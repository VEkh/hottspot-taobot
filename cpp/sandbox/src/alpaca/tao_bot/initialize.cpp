#ifndef ALPACA__TAO_BOT_initialize
#define ALPACA__TAO_BOT_initialize

#include "alpaca/client/client.cpp"  // Alpaca::Client
#include "build_performance.cpp"     // build_performance
#include "fetch_account_balance.cpp" // fetch_account_balance
#include "fetch_quote.cpp"           // fetch_quote
#include "lib/formatted.cpp"         // Formatted::error_message
#include "lib/utils/boolean.cpp"     // ::utils::boolean
#include "load_performance.cpp"      // load_performance
#include "tao_bot.h"                 // Alpaca::TaoBot
#include <locale.h>                  // setlocale
#include <map>                       // std::map
#include <stdexcept>                 // std::invalid_argument
#include <string>                    // std::string

void Alpaca::TaoBot::initialize(char *symbol_,
                                std::map<std::string, std::string> &flags) {
  if (symbol_ == nullptr) {
    std::string message = Formatted::error_message("Must provide a symbol");
    throw std::invalid_argument(message);
  }

  // Support comma separation in print output
  setlocale(LC_NUMERIC, "");

  this->api_client = Alpaca::Client(flags);

  this->account_balance = this->original_account_balance =
      fetch_account_balance();

  this->flags = flags;
  this->symbol = symbol_;

  fetch_quote();
  load_performance();

  this->performance = build_performance();
  this->is_long_position = true;
}

#endif
