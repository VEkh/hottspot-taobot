#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

#include "stock_bot.h" // ETrade::StockBot, quote_t
#include <math.h>      // abs

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  const quote_t current_quote = this->quotes.back();

  const double entry_velocity = 0.05;
  const double buy_sell_velocity =
      current_quote.simple_moving_average.average_buy_sell_velocity;

  if (abs(buy_sell_velocity) >= entry_velocity) {
    this->is_long_position = buy_sell_velocity > 0;

    return true;
  }

  return false;
}

#endif
