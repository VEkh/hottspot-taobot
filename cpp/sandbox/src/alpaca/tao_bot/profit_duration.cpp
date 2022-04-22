#ifndef ALPACA__TAO_BOT_profit_duration
#define ALPACA__TAO_BOT_profit_duration

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max
#include <ctime>     // std::time

int Alpaca::TaoBot::profit_duration() {
  return std::max(0.0, std::time(nullptr) - this->profit_started_at);
}

#endif