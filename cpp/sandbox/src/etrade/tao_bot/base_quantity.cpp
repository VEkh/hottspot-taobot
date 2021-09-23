#ifndef ETRADE__TAO_BOT_base_quantity
#define ETRADE__TAO_BOT_base_quantity

#include "tao_bot.h" // ETrade::TaoBot
#include <math.h>    // ceil, pow

int ETrade::TaoBot::base_quantity() {
  const double current_price = this->quotes.back().current_price;
  const double max_allowable_margin_ratio = 2.0 / 3.0;
  const int margin_multiplier = 4;

  const double max_order_price =
      (max_allowable_margin_ratio * this->account_balance.balance *
       margin_multiplier);

  const double basis_price =
      max_order_price / pow(2, this->MAX_EXPECTED_LOSS_STREAK);

  const int base_quantity_ = ceil(basis_price / current_price);

  return this->quantity_mulitiplier * base_quantity_;
}

#endif
