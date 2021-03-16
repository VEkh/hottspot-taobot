#if !defined ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

/*
 * ETrade::StockBot
 * order_status_t
 * quote_t
 */
#include "stock_bot.h"

#include <math.h> // abs

bool ETrade::StockBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_PENDING) {
    return false;
  }

  const quote_t current_quote = this->quotes.back();

  const double exit_velocity = 0.02;
  const double buy_sell_velocity =
      current_quote.simple_moving_average.average_buy_sell_velocity;

  if (abs(buy_sell_velocity) <= exit_velocity) {
    return true;
  }

  return false;
}

#endif
