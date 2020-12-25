#if !defined TD_AMERITRADE__STRADDLE
#define TD_AMERITRADE__STRADDLE

#include "straddle.h" // TdAmeritrade::Straddle, quantity, symbol, td_ameritrade_client
#include "lib/formatted.cpp" // Formatted::error_message
#include "manual_run.cpp"
#include <stdexcept> // std::invalid_argument

TdAmeritrade::Straddle::Straddle(char *symbol_) {
  if (symbol_ == nullptr) {
    std::string message = Formatted::error_message("Must provide a symbol");
    throw std::invalid_argument(message);
  }

  symbol = symbol_;
}

TdAmeritrade::Straddle::Straddle(char *symbol_, int quantity_) {
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
