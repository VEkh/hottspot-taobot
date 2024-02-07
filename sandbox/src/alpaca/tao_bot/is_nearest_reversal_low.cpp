#ifndef ALPACA__TAO_BOT_is_nearest_reversal_low
#define ALPACA__TAO_BOT_is_nearest_reversal_low

#include "nearest_reversal.cpp" // nearest_reversal
#include "tao_bot.h"            // Alpaca::TaoBot

bool Alpaca::TaoBot::is_nearest_reversal_low() {
  return nearest_reversal().type == reversal_type_t::REVERSAL_LOW;
}

#endif
