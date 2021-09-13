#ifndef ETRADE__TAO_BOT_compute_normalized_quantity
#define ETRADE__TAO_BOT_compute_normalized_quantity

#include "fetch_account_balance.cpp"          // fetch_account_balance
#include "martingale_quantity_multiplier.cpp" // martingale_quantity_multiplier
#include "tao_bot.h"                        // ETrade::TaoBot
#include <math.h>                             // ceil, pow

int ETrade::TaoBot::compute_normalized_quantity() {
  int final_multiplier =
      this->quantity_mulitiplier * martingale_quantity_multiplier();

  if (!this->FLAG_NORMALIZE_QUANTITY) {
    return final_multiplier;
  }

  this->account_balance = fetch_account_balance();

  const double current_price = this->quotes.back().current_price;
  const double max_allowable_margin_ratio = 2.0 / 3.0;
  const int margin_multiplier = 4;

  const double max_order_price =
      (max_allowable_margin_ratio * this->account_balance.balance *
       margin_multiplier);

  const double basis_price =
      max_order_price / pow(2, this->MAX_EXPECTED_LOSS_STREAK);
  const double normalized_quantity = ceil(basis_price / current_price);

  return final_multiplier * normalized_quantity;
}

#endif
