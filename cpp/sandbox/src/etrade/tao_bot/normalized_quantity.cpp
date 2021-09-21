#ifndef ETRADE__TAO_BOT_normalized_quantity
#define ETRADE__TAO_BOT_normalized_quantity

#include "martingale_quantity_multiplier.cpp" // martingale_quantity_multiplier
#include "tao_bot.h"                          // ETrade::TaoBot
#include <algorithm>                          // std::min
#include <math.h>                             // ceil, pow

int ETrade::TaoBot::normalized_quantity() {
  const double current_price = this->quotes.back().current_price;
  const double max_allowable_margin_ratio = 2.0 / 3.0;

  int max_affordable_quantity =
      (int)(0.95 * this->account_balance.day_trading_margin_buying_power /
            current_price);

  int final_multiplier =
      this->quantity_mulitiplier * martingale_quantity_multiplier();

  if (!this->FLAG_NORMALIZE_QUANTITY) {
    return std::min(final_multiplier, max_affordable_quantity);
  }

  const int margin_multiplier = 4;

  const double max_order_price =
      (max_allowable_margin_ratio * this->account_balance.balance *
       margin_multiplier);

  const double basis_price =
      max_order_price / pow(2, this->MAX_EXPECTED_LOSS_STREAK);
  const int normalized_quantity_ = ceil(basis_price / current_price);

  return std::min(final_multiplier * normalized_quantity_,
                  max_affordable_quantity);
}

#endif
