#ifndef ALPACA__TAO_BOT_ensure_symbol
#define ALPACA__TAO_BOT_ensure_symbol

#include "lib/formatted.cpp" // Formatted::error_message
#include "tao_bot.h"         // Alpaca::TaoBot
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

void Alpaca::TaoBot::ensure_symbol(const std::string symbol_) {
  if (symbol_.empty()) {
    const std::string message =
        Formatted::error_message("Must provide a symbol");

    throw std::invalid_argument(message);
  }
}

#endif
