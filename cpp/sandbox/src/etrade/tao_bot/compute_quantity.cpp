#ifndef ETRADE__TAO_BOT_compute_quantity
#define ETRADE__TAO_BOT_compute_quantity

#include "base_quantity.cpp"   // base_quantity
#include "loss_to_recover.cpp" // loss_to_recover
#include "tao_bot.h"           // ETrade::TaoBot
#include <algorithm>           // std::min
#include <math.h>              // abs, ceil, floor

int ETrade::TaoBot::compute_quantity() {
  const double current_price = this->quotes.back().current_price;
  double loss_to_recover_ = loss_to_recover();

  if (!loss_to_recover_) {
    return base_quantity();
  }

  loss_to_recover_ = abs(loss_to_recover_);
  int max_affordable_quantity =
      floor(0.6 * this->account_balance.day_trading_margin_buying_power /
            current_price);

  int variance_multiplier = 20;
  int quantity_ = 1;

  while (variance_multiplier <= 40 && quantity_ < max_affordable_quantity) {
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
