#ifndef ALPACA__TAO_BOT_is_end_of_quotes
#define ALPACA__TAO_BOT_is_end_of_quotes

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::is_end_of_quotes() {
  if (!this->backtest.is_active) {
    return false;
  }

  if (this->quotes.empty()) {
    return false;
  }

  return this->current_quote.timestamp == this->quotes.back().timestamp;
}

#endif
