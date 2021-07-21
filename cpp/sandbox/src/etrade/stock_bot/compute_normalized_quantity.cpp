#ifndef ETRADE__STOCK_BOT_compute_normalized_quantity
#define ETRADE__STOCK_BOT_compute_normalized_quantity

#include "fetch_account_balance.cpp"          // fetch_account_balance
#include "martingale_quantity_multiplier.cpp" // martingale_quantity_multiplier
#include "stock_bot.h"                        // ETrade::StockBot
#include <math.h>                             // ceil, pow

int ETrade::StockBot::compute_normalized_quantity() {
  int final_multiplier =
      this->quantity_mulitiplier * martingale_quantity_multiplier();

  if (!this->FLAG_NORMALIZE_QUANTITY) {
    return final_multiplier;
  }

  this->account_balance = fetch_account_balance();

  const double current_price = this->quotes.back().current_price;
  const int margin_multiplier = 4;
  const int max_allowed_losses = 8;

  const double max_order_price =
      (0.8 * this->account_balance.balance * margin_multiplier);

  const double basis_price = max_order_price / pow(2, max_allowed_losses);
  const double normalized_quantity = ceil(basis_price / current_price);

  return final_multiplier * normalized_quantity;
}

#endif
