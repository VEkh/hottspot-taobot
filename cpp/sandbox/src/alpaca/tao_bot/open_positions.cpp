#ifndef ALPACA__TAO_BOT_open_positions
#define ALPACA__TAO_BOT_open_positions

#include "open_hedged_position.cpp" // open_hedged_position
#include "tao_bot.h"                // Alpaca::TaoBot

void Alpaca::TaoBot::open_positions() { return open_hedged_position(); }

#endif
