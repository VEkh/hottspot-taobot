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

  const int consecutive_ticks = 5;
  int i = 0;
  int negative_count = 0;
  int positive_count = 0;

  std::vector<quote_t>::reverse_iterator it;

  for (it = this->quotes.rbegin(); i < consecutive_ticks; it++) {
    const double acceleration = it->simple_moving_average.acceleration;

    if (acceleration > 0) {
      positive_count++;
    } else if (acceleration < 0) {
      negative_count++;
    }

    i++;
  }

  if (this->is_long_position && negative_count >= consecutive_ticks) {
    return true;
  } else if (!this->is_long_position && positive_count >= consecutive_ticks) {
    return true;
  }

  return false;
}

#endif
