#ifndef ALPACA__TAO_BOT_max_affordable_quantity
#define ALPACA__TAO_BOT_max_affordable_quantity

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // Alpaca::TaoBot

double Alpaca::TaoBot::max_affordable_quantity() {
  return this->account_balance.margin_buying_power / current_price();
}

#endif
