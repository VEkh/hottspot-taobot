#ifndef OANDA__TAO_BOT_set_and_persist_price_movement
#define OANDA__TAO_BOT_set_and_persist_price_movement

#include "set_price_movement.cpp"   // set_price_movement
#include "tao_bot.h"                // Oanda::TaoBot
#include "write_price_movement.cpp" // write_price_movement

void Oanda::TaoBot::set_and_persist_price_movement() {
  set_price_movement();
  write_price_movement();
}

#endif
