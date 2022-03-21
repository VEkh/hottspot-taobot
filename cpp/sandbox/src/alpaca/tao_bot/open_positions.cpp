#ifndef ALPACA__TAO_BOT_open_positions
#define ALPACA__TAO_BOT_open_positions

#include "is_hedging.cpp"               // is_hedging
#include "open_hedged_position.cpp"     // open_hedged_position
#include "open_martingale_position.cpp" // open_martingale_position
#include "tao_bot.h"                    // Alpaca::TaoBot

void Alpaca::TaoBot::open_positions() {
  return is_hedging() ? open_hedged_position() : open_martingale_position();
}

#endif
