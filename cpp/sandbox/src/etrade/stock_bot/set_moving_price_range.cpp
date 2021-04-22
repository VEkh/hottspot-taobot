#if !defined ETRADE__STOCK_BOT_set_moving_price_range
#define ETRADE__STOCK_BOT_set_moving_price_range

#include "stock_bot.h" // ETrade::StockBot, quote_t
#include <algorithm>   // std::max, std::min
#include <vector>      // std::vector

void ETrade::StockBot::set_moving_price_range(const int period_seconds) {
  double high = -INFINITY;
  double low = INFINITY;
  int period;

  std::vector<quote_t>::reverse_iterator it = this->quotes.rbegin();
  const quote_t current_quote = this->quotes.back();

  while (it != this->quotes.rend() &&
         current_quote.timestamp - it->timestamp <= period_seconds) {
    high = std::max(high, it->current_price);
    low = std::min(low, it->current_price);
    period = current_quote.timestamp - it->timestamp;
    it++;
  }

  this->moving_price_range = {.high = high, .low = low, .period = period};
}

#endif
