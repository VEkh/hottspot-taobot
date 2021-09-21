#ifndef OANDA__TAO_BOT_initialize
#define OANDA__TAO_BOT_initialize

#include "lib/formatted.cpp" // Formatted::error_message
#include "tao_bot.h"         // Oanda::TaoBot, quantity, symbol
#include <locale.h>          // setlocale
#include <stdexcept>         // std::invalid_argument

void Oanda::TaoBot::initialize(char *symbol_, int quantity_mulitiplier_,
                               std::map<std::string, std::string> &flags) {
  if (symbol_ == nullptr) {
    std::string message =
        Formatted::error_message("Must provide a currency pair");
    throw std::invalid_argument(message);
  }

  if (!quantity_mulitiplier_) {
    std::string message =
        Formatted::error_message("Quantity must be at least 1");

    throw std::invalid_argument(message);
  }

  // Support comma separation in print output
  setlocale(LC_NUMERIC, "");

  this->FLAG_MARTINGALE = flags["martingale"] == "1";
  this->FLAG_NORMALIZE_QUANTITY = flags["normalize-quantity"] == "1";
  this->symbol = symbol_;
  this->quantity_mulitiplier = quantity_mulitiplier_;
  this->quantity = quantity_mulitiplier_;
}

#endif
