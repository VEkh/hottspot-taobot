#ifndef ALPACA__TAO_BOT_max_affordable_quantity
#define ALPACA__TAO_BOT_max_affordable_quantity

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // floor

double Alpaca::TaoBot::max_affordable_quantity() {
  account_balance_t account_balance_ = this->account_balance;
  bool is_long_position_ = true;

  if (this->hedge_account_balance.balance &&
      this->hedge_account_balance.balance < this->account_balance.balance) {
    account_balance_ = this->hedge_account_balance;
    is_long_position_ = false;
  }

  const quote_t current_quote = this->quotes.back();

  const double current_price_ =
      is_long_position_ ? 1.04 * current_quote.price : 1.03 * current_quote.ask;

  const double quantity_ =
      account_balance_.margin_buying_power / current_price_;

  return is_long_position_ ? quantity_ : floor(quantity_);
}

#endif
