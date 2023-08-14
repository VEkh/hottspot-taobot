#ifndef OANDA__TAO_BOT_spread_limit
#define OANDA__TAO_BOT_spread_limit

#include "tao_bot.h" // Oanda::TaoBot

double Oanda::TaoBot::spread_limit() {
  return this->SPREAD_LIMITS[std::string(this->symbol)];
}

#endif
