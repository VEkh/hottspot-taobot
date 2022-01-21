#ifndef ALPACA__TAO_BOT_max_affordable_quantity
#define ALPACA__TAO_BOT_max_affordable_quantity

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // floor

double Alpaca::TaoBot::max_affordable_quantity() {
  const quote_t current_quote = this->quotes.back();

  const double current_price_ = this->is_long_position
                                    ? 1.04 * current_quote.price
                                    : 1.03 * current_quote.ask;
  const double quantity_ =
      this->account_balance.margin_buying_power / current_price_;

  return this->is_long_position ? quantity_ : floor(quantity_);
}

#endif
