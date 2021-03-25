#if !defined ETRADE__STOCK_BOT_compute_door_moving_average_period
#define ETRADE__STOCK_BOT_compute_door_moving_average_period

#include "stock_bot.h" // ETrade::StockBot, quote_t
#include <algorithm>   // std::max, std::min
#include <math.h>      // INFINITY, exp
#include <vector>      // std::vector

double ETrade::StockBot::compute_door_moving_average_period() {
  return 2 * 60;

  const double max_period = 5 * 60;
  const double min_period = 1 * 60;
  const int range_period = 2 * 60;
  const quote_t current_quote = this->quotes.back();
  const quote_t first_quote = this->quotes.front();

  if (current_quote.timestamp - first_quote.timestamp < range_period) {
    return min_period;
  }

  double high = -INFINITY;
  double low = INFINITY;
  quote_t start_quote;
  std::vector<quote_t>::reverse_iterator it;

  for (it = this->quotes.rbegin();
       (current_quote.timestamp - it->timestamp) <= range_period; it++) {
    start_quote = *it;
    high = std::max(high, start_quote.current_price);
    low = std::min(low, start_quote.current_price);
  }

  std::cout << "current quote first quote time delta: "
            << (current_quote.timestamp - start_quote.timestamp) << std::endl;

  const double open = it->current_price;
  const double range_percentage = 100 * ((high - low) / open);
  const double x = range_percentage;
  const double x_scale = -15;
  const double x_shift = -0.2;
  const double y_scale = max_period - min_period;
  const double y_shift = min_period;

  std::cout << "high: " << high << std::endl;
  std::cout << "low: " << low << std::endl;
  std::cout << "range percentage: " << range_percentage << std::endl;

  const double y = (y_scale / (1 + exp(x_scale * (x + x_shift)))) + y_shift;

  return y;
}

#endif
