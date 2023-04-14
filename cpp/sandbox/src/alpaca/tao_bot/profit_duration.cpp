#ifndef ALPACA__TAO_BOT_profit_duration
#define ALPACA__TAO_BOT_profit_duration

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max

int Alpaca::TaoBot::profit_duration(const double timestamp) {
  return std::max(0.0, this->current_epoch - timestamp);
}

#endif
