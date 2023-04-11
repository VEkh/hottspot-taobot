#ifndef ALPACA__TAO_BOT_current_price
#define ALPACA__TAO_BOT_current_price

#include "tao_bot.h" // Alpaca::TaoBot

double Alpaca::TaoBot::current_price() { return this->quotes.front().price; }

#endif
