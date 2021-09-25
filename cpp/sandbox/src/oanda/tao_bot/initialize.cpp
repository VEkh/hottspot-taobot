#ifndef OANDA__TAO_BOT_initialize
#define OANDA__TAO_BOT_initialize

#include "fetch_account_balance.cpp" // fetch_account_balance
#include "lib/formatted.cpp"         // Formatted::error_message
#include "tao_bot.h"                 // Oanda::TaoBot, quantity, symbol
#include <locale.h>                  // setlocale
#include <stdexcept>                 // std::invalid_argument

void Oanda::TaoBot::initialize(char *symbol_,
                               std::map<std::string, std::string> &flags) {
  if (symbol_ == nullptr) {
    std::string message =
        Formatted::error_message("Must provide a currency pair");
    throw std::invalid_argument(message);
  }

  // Support comma separation in print output
  setlocale(LC_NUMERIC, "");

  this->account_balance = this->original_account_balance =
      fetch_account_balance();
  this->symbol = symbol_;
}

#endif
