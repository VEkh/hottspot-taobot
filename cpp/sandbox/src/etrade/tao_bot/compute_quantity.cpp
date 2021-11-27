#ifndef ETRADE__TAO_BOT_compute_quantity
#define ETRADE__TAO_BOT_compute_quantity

#include "base_quantity.cpp"           // base_quantity
#include "loss_to_recover.cpp"         // loss_to_recover
#include "max_affordable_quantity.cpp" // max_affordable_quantity
#include "tao_bot.h"                   // ETrade::TaoBot
#include <algorithm>                   // std::min
#include <math.h>                      // abs, ceil

int ETrade::TaoBot::compute_quantity() {
  const int max_affordable_quantity_ = max_affordable_quantity();

  if (!max_affordable_quantity_) {
    return 0;
  }

  const double loss_to_recover_ = abs(loss_to_recover());

  if (!loss_to_recover_) {
    return std::min(base_quantity(), max_affordable_quantity_);
  }

  int quantity_ =
      ceil(1.05 * loss_to_recover_ /
           (this->MIN_TARGET_TICK_MOVEMENT * this->average_tick_price_delta));

  return std::min(quantity_, max_affordable_quantity_);
}

#endif
