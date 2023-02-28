#ifndef ALPACA__TAO_BOT_initialize
#define ALPACA__TAO_BOT_initialize

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "build_performance.cpp"    // build_performance
#include "get_account_balance.cpp"  // get_account_balance
#include "is_holiday.cpp"           // is_holiday
#include "lib/formatted.cpp"        // Formatted::error_message
#include "lib/utils/boolean.cpp"    // ::utils::boolean
#include "lib/utils/string.cpp"     // ::utils::string
#include "load_performance.cpp"     // load_performance
#include "tao_bot.h"                // Alpaca::TaoBot
#include <iostream>                 // std::cout, std::endl
#include <locale.h>                 // setlocale
#include <map>                      // std::map
#include <stdexcept>                // std::invalid_argument, std::runtime_error
#include <string>                   // std::string

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
  this->symbol = ::utils::string::upcase(symbol_);

  try {
    this->api_client = Alpaca::Client(this->flags);

    this->account_balance = get_account_balance();

    load_performance();

    this->init_closed_positions_count = this->closed_positions.size();
    this->performance = build_performance();
  } catch (nlohmann::detail::type_error) {
    puts(Formatted::error_message(
             "❌ JSON type error during initialization. Retrying.")
             .c_str());
    return initialize(symbol_, flags_);
  }
}

#endif
