#ifndef ETRADE__TAO_BOT_compute_quantity
#define ETRADE__TAO_BOT_compute_quantity

#include "base_quantity.cpp"   // base_quantity
#include "current_price.cpp"   // current_price
#include "loss_to_recover.cpp" // loss_to_recover
#include "tao_bot.h"           // ETrade::TaoBot
#include <algorithm>           // std::min
#include <math.h>              // abs, ceil, floor

int ETrade::TaoBot::compute_quantity() {
  const int max_affordable_quantity =
      floor(this->account_balance.margin_buying_power / current_price());

  if (!max_affordable_quantity) {
    return 0;
  }

  const double loss_to_recover_ = abs(loss_to_recover());

  if (!loss_to_recover_) {
    return std::min(base_quantity(), max_affordable_quantity);
  }

  int quantity_ =
      ceil(1.05 * loss_to_recover_ /
           (this->MIN_TARGET_TICK_MOVEMENT * this->average_tick_price_delta));

  return std::min(quantity_, max_affordable_quantity);
}

#endif
