#ifndef OANDA__TAO_BOT_ensure_symbol
#define OANDA__TAO_BOT_ensure_symbol

#include "lib/formatted.cpp" // Formatted::error_message
#include "tao_bot.h"         // Oanda::TaoBot
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

void Oanda::TaoBot::ensure_symbol(const std::string symbol_) {
  if (symbol_.empty()) {
    const std::string message =
        Formatted::error_message("Must provide a currency pair");

    throw std::invalid_argument(message);
  }
}

#endif
