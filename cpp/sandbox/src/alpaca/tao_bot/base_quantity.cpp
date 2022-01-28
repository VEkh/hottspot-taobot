#ifndef ALPACA__TAO_BOT_base_quantity
#define ALPACA__TAO_BOT_base_quantity

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // Alpaca::TaoBot
#include <math.h>            // pow

double Alpaca::TaoBot::base_quantity() {
  const double max_buying_potential =
      this->account_balance.balance * this->account_balance.margin_multiplier;

  const double max_affordable_quantity_ =
      max_buying_potential / current_price();

  return max_affordable_quantity_ / pow(2, this->MAX_EXPECTED_LOSS_STREAK + 1);
}

#endif
