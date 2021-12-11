#ifndef OANDA__TAO_BOT_max_affordable_quantity
#define OANDA__TAO_BOT_max_affordable_quantity

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // Oanda::TaoBot
#include <math.h>            // floor

int Oanda::TaoBot::max_affordable_quantity() {
  return floor(this->account_balance.margin_buying_power / current_price());
}

#endif
