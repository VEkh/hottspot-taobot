#if !defined ETRADE__STOCK_BOT_BETA_initialize
#define ETRADE__STOCK_BOT_BETA_initialize

#include "lib/formatted.cpp" // Formatted::error_message
#include "stock_bot_beta.h"  // ETrade::StockBotBeta, quantity, symbol
#include <stdexcept>         // std::invalid_argument

void ETrade::StockBotBeta::initialize(char *symbol_, int quantity_) {
  if (symbol_ == nullptr) {
    std::string message = Formatted::error_message("Must provide a symbol");
    throw std::invalid_argument(message);
  }

  if (!quantity_) {
    std::string message =
        Formatted::error_message("Quantity must be at least 1");

    throw std::invalid_argument(message);
  }

  symbol = symbol_;
  quantity = quantity_;
}

#endif
