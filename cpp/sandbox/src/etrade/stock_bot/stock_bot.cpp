#if !defined ETRADE__STOCK_BOT
#define ETRADE__STOCK_BOT

#include "lib/formatted.cpp" // Formatted::error_message
#include "manual_run.cpp"
#include "run.cpp"
#include "stock_bot.h" // ETrade::StockBot, quantity, symbol, etrade_client
#include <stdexcept>   // std::invalid_argument

ETrade::StockBot::StockBot(char *symbol_) {
  if (symbol_ == nullptr) {
    std::string message = Formatted::error_message("Must provide a symbol");
    throw std::invalid_argument(message);
  }

  symbol = symbol_;
}

ETrade::StockBot::StockBot(char *symbol_, int quantity_) {
  initialize(symbol_, quantity_);
}

ETrade::StockBot::StockBot(char *symbol_, int quantity_,
                           char *init_order_action_) {
  init_order_action = init_order_action_;
  initialize(symbol_, quantity_);
}

void ETrade::StockBot::initialize(char *symbol_, int quantity_) {
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
