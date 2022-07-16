#ifndef ALPACA__TAO_BOT_open_positions
#define ALPACA__TAO_BOT_open_positions

#include "open_and_persist_position.cpp" // open_and_persist_position
#include "tao_bot.h"                     // Alpaca::TaoBot

void Alpaca::TaoBot::open_positions() { return open_and_persist_position(); }

#endif
