#if !defined ETRADE__STRADDLE
#define ETRADE__STRADDLE

#include "straddle.h" // ETrade::Straddle, quantity, symbol, etrade_client
#include "lib/formatted.cpp" // Formatted::error_message
#include "manual_run.cpp"
#include "run.cpp"
#include <stdexcept> // std::invalid_argument

ETrade::Straddle::Straddle(char *symbol_) {
  if (symbol_ == nullptr) {
    std::string message = Formatted::error_message("Must provide a symbol");
    throw std::invalid_argument(message);
  }

  symbol = symbol_;
}

ETrade::Straddle::Straddle(char *symbol_, int quantity_) {
  initialize(symbol_, quantity_);
}

ETrade::Straddle::Straddle(char *symbol_, int quantity_,
                           char *init_order_action_) {
  init_order_action = init_order_action_;
  initialize(symbol_, quantity_);
}

void ETrade::Straddle::initialize(char *symbol_, int quantity_) {
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
