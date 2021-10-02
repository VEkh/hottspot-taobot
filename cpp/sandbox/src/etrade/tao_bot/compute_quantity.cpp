#ifndef ETRADE__TAO_BOT_compute_quantity
#define ETRADE__TAO_BOT_compute_quantity

#include "base_quantity.cpp"   // base_quantity
#include "loss_to_recover.cpp" // loss_to_recover
#include "tao_bot.h"           // ETrade::TaoBot
#include <algorithm>           // std::min
#include <math.h>              // abs, ceil, floor

int ETrade::TaoBot::compute_quantity() {
  const double price = this->quotes.back().price;

  const int max_affordable_quantity =
      floor(this->account_balance.margin_buying_power / price);

  if (!max_affordable_quantity) {
    return 0;
  }

  const double loss_to_recover_ = abs(loss_to_recover());

  if (!loss_to_recover_) {
    return std::min(base_quantity(), max_affordable_quantity);
  }

  int variance_multiplier = this->MIN_TARGET_TICK_MOVEMENT;
  int quantity_ = 1;

  while (variance_multiplier <= this->MAX_TARGET_TICK_MOVEMENT &&
         quantity_ < max_affordable_quantity) {
    quantity_ = ceil(loss_to_recover_ /
                     (variance_multiplier * this->average_tick_price_delta));

    if (quantity_ <= max_affordable_quantity) {
      return quantity_;
    }

    variance_multiplier++;
  }

  return std::min(quantity_, max_affordable_quantity);
}

#endif
