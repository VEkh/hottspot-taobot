#ifndef ALPACA__TAO_BOT_initialize
#define ALPACA__TAO_BOT_initialize

#include "alpaca/client/client.cpp"    // Alpaca::Client
#include "build_performance.cpp"       // build_performance
#include "fetch_and_persist_quote.cpp" // fetch_and_persist_quote
#include "get_account_balance.cpp"     // get_account_balance
#include "is_holiday.cpp"              // is_holiday
#include "lib/formatted.cpp"           // Formatted::error_message
#include "lib/utils/boolean.cpp"       // ::utils::boolean
#include "load_performance.cpp"        // load_performance
#include "load_price_movement.cpp"     // load_rice_movement
#include "load_quotes.cpp"             // load_quotes
#include "tao_bot.h"                   // Alpaca::TaoBot
#include <iostream>                    // std::cout, std::endl
#include <locale.h>                    // setlocale
#include <map>                         // std::map
#include <stdexcept> // std::invalid_argument, std::runtime_error
#include <string>    // std::string

void Alpaca::TaoBot::initialize(char *symbol_,
                                std::map<std::string, std::string> &flags_) {
  if (symbol_ == nullptr) {
    const std::string message =
        Formatted::error_message("Must provide a symbol");

    throw std::invalid_argument(message);
  }

  if (is_holiday()) {
    const std::string message = Formatted::error_message(
        "🎉 Today is a holiday! The markets are closed, so go have "
        "fun yabish!! 🥳 ");

    throw std::runtime_error(message);
  }

  // Support comma separation in print output
  setlocale(LC_NUMERIC, "");

  this->flags = flags_;
  this->symbol = symbol_;

  this->api_client = Alpaca::Client(this->flags);

  this->account_balance = this->original_account_balance =
      get_account_balance();

  load_quotes();

  fetch_and_persist_quote();
  load_performance();
  load_price_movement();

  this->performance = build_performance();
}

#endif
