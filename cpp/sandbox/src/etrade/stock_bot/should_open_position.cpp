#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

#include "stock_bot.h" // ETrade::StockBot, quote_t
#include <math.h>      // abs

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  const int ticks = 6;

  if (this->quotes.size() < ticks) {
    return false;
  }

  int i = 0;
  const quote_t current_quote = this->quotes.back();
  const double buy_sell_ratio =
      current_quote.simple_moving_average.buy_sell_ratio;
  const double sell_buy_ratio =
      current_quote.simple_moving_average.sell_buy_ratio;
  double total_velocity;

  std::vector<quote_t>::reverse_iterator it;

  for (it = this->quotes.rbegin(); i < ticks; it++) {
    total_velocity += it->simple_moving_average.velocity;
    i++;
  }

  const double average_velocity = total_velocity / ticks;
  const double buy_sell_threshold = 1.2;
  const double velocity_threshold = 0.2;

  if (buy_sell_ratio >= buy_sell_threshold &&
      average_velocity >= velocity_threshold) {
    this->is_long_position = true;
    return true;
  } else if (sell_buy_ratio >= buy_sell_threshold &&
             average_velocity <= -velocity_threshold) {
    this->is_long_position = false;
    return true;
  }

  return false;
}

#endif
