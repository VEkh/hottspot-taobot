#ifndef ALPACA__TAO_BOT_log_price_movements
#define ALPACA__TAO_BOT_log_price_movements

#include "log_price_movement.cpp" // log_price_movement
#include "tao_bot.h"              // Alpaca::TaoBot

void Alpaca::TaoBot::log_price_movements() { log_price_movement(this->symbol); }

#endif
