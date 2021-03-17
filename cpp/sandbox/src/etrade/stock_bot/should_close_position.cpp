#if !defined ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

#include "stock_bot.h" // ETrade::StockBot, order_status_t, quote_t

bool ETrade::StockBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_PENDING) {
    return false;
  }

  const int ticks = 10;
  int i = 0;
  double total_velocity;

  std::vector<quote_t>::reverse_iterator it;

  for (it = this->quotes.rbegin(); i < ticks; it++) {
    total_velocity += it->simple_moving_average.velocity;
    i++;
  }

  const double average_velocity = total_velocity / ticks;
  const double exit_threshold = 0.2;

  if (this->is_long_position && average_velocity <= -exit_threshold) {
    return true;
  } else if (!this->is_long_position && average_velocity >= exit_threshold) {
    return true;
  }

  return false;
}

#endif
