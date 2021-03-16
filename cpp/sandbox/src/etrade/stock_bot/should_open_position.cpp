#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

#include "stock_bot.h" // ETrade::StockBot, quote_t
#include <vector>      // std::vector

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  const int consecutive_ticks = 15;
  int i = 0;
  int negative_velocity_count = 0;
  int positive_velocity_count = 0;

  std::vector<quote_t>::reverse_iterator it;

  for (it = this->quotes.rbegin(); i < consecutive_ticks; it++) {
    const double velocity = it->simple_moving_average.velocity;

    if (velocity > 0) {
      positive_velocity_count++;
    } else if (velocity < 0) {
      negative_velocity_count++;
    }

    i++;
  }

  if (negative_velocity_count == consecutive_ticks ||
      positive_velocity_count == consecutive_ticks) {
    this->is_long_position = positive_velocity_count == consecutive_ticks;

    return true;
  }

  return false;
}

#endif
