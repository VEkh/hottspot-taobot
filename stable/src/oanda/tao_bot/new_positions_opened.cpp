#ifndef OANDA__TAO_BOT_new_positions_opened
#define OANDA__TAO_BOT_new_positions_opened

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::new_positions_opened() {
  return !this->closed_positions.empty();
}

#endif
