#ifndef ETRADE__TAO_BOT_max_affordable_quantity
#define ETRADE__TAO_BOT_max_affordable_quantity

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // ETrade::TaoBot
#include <math.h>            // floor

int ETrade::TaoBot::max_affordable_quantity() {
  return floor(this->account_snapshot.margin_buying_power / current_price());
}

#endif
