#ifndef ETRADE__TAO_BOT_set_trade_direction
#define ETRADE__TAO_BOT_set_trade_direction

#include "set_trade_direction.cpp" // set_trade_direction
#include "flip_coin.cpp"           // flip_coin
#include "iostream"                // std::count
#include "stdio.h"                 // puts
#include "tao_bot.h"               // ETrade::TaoBot, fmt

void ETrade::TaoBot::set_trade_direction() { this->is_long_position = true; }

#endif
