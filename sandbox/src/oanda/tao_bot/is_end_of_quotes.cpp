#ifndef OANDA__TAO_BOT_is_end_of_quotes
#define OANDA__TAO_BOT_is_end_of_quotes

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::is_end_of_quotes() {
  if (this->quotes.empty()) {
    return false;
  }

  return this->current_quote.timestamp == this->quotes.back().timestamp;
}

#endif
