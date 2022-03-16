#ifndef ALPACA__TAO_BOT_compute_hedge_quantity
#define ALPACA__TAO_BOT_compute_hedge_quantity

#include "build_exit_prices.cpp"       // build_exit_prices
#include "loss_to_recover.cpp"         // loss_to_recover
#include "max_affordable_quantity.cpp" // max_affordable_quantity
#include "secured_profit_ratio.cpp"    // secured_profit_ratio
#include "tao_bot.h"                   // Alpaca::TaoBot
#include <algorithm>                   // std::min
#include <math.h>                      // ceil, floor

double Alpaca::TaoBot::compute_hedge_quantity() {
  const double max_affordable_quantity_ = max_affordable_quantity();

  if (!max_affordable_quantity_) {
    return 0;
  }

  const double loss_to_recover_ = abs(loss_to_recover());

  if (!loss_to_recover_) {
    return std::min(1.0, max_affordable_quantity_);
  }

  const double secured_profit_ratio_ =
      secured_profit_ratio(this->open_order_ptr);

  const exit_prices_t exit_prices_ = build_exit_prices(this->open_order_ptr);

  const double recovery_profit =
      abs(exit_prices_.max_loss / secured_profit_ratio_) -
      abs(exit_prices_.max_loss);

  const double quantity_ = loss_to_recover_ / recovery_profit;

  return std::min(ceil(quantity_), floor(max_affordable_quantity_));
}

#endif
