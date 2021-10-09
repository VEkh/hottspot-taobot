#ifndef ETRADE__TAO_BOT_initialize
#define ETRADE__TAO_BOT_initialize

#include "build_performance.cpp"     // build_performance
#include "fetch_account_balance.cpp" // fetch_account_balance
#include "lib/formatted.cpp"         // Formatted::error_message
#include "load_performance.cpp"      // load_performance
#include "tao_bot.h"                 // ETrade::TaoBot, quantity, symbol
#include <locale.h>                  // setlocale
#include <stdexcept>                 // std::invalid_argument

void ETrade::TaoBot::initialize(char *symbol_, int quantity_mulitiplier_,
                                std::map<std::string, std::string> &flags) {
  if (symbol_ == nullptr) {
    std::string message = Formatted::error_message("Must provide a symbol");
    throw std::invalid_argument(message);
  }

  if (!quantity_mulitiplier_) {
    std::string message =
        Formatted::error_message("Quantity must be at least 1");

    throw std::invalid_argument(message);
  }

  // Support comma separation in print output
  setlocale(LC_NUMERIC, "");

  this->account_balance = this->original_account_balance =
      fetch_account_balance();
  this->symbol = symbol_;
  this->quantity_mulitiplier = quantity_mulitiplier_;
  this->quantity = quantity_mulitiplier_;

  load_performance();

  this->performance = build_performance();
}

#endif
