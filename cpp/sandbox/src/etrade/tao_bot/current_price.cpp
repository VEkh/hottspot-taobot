#ifndef ETRADE__TAO_BOT_current_price
#define ETRADE__TAO_BOT_current_price

#include "tao_bot.h" // ETrade::TaoBot

double ETrade::TaoBot::current_price() { return this->quotes.back().price; }

#endif
