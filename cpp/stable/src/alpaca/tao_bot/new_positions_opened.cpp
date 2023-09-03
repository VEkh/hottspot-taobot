#ifndef ALPACA__TAO_BOT_new_positions_opened
#define ALPACA__TAO_BOT_new_positions_opened

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::new_positions_opened() {
  return !this->closed_positions.empty();
}

#endif
