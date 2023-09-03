#ifndef OANDA__TAO_BOT_current_price
#define OANDA__TAO_BOT_current_price

#include "tao_bot.h" // Oanda::TaoBot

double Oanda::TaoBot::current_price() { return this->quotes.back().price; }

#endif
