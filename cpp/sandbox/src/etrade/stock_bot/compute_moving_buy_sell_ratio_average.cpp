#if !defined ETRADE__STOCK_BOT_compute_moving_buy_sell_ratio_average
#define ETRADE__STOCK_BOT_compute_moving_buy_sell_ratio_average

#include "stock_bot.h" // ETrade::StockBot, quote_t
#include <vector>      // std::vector

double
ETrade::StockBot::compute_moving_buy_sell_ratio_average(const int seconds) {
  const quote_t current_quote = this->quotes.back();

  double total;
  int count = 0;

  std::vector<quote_t>::reverse_iterator it = this->quotes.rbegin();

  while (it != this->quotes.rend() &&
         current_quote.timestamp - it->timestamp <= seconds) {
    if (!it->simple_moving_average.buy_sell_ratio) {
      return 0;
    }

    total += it->simple_moving_average.buy_sell_ratio;

    it++;
    count++;
  }

  return total / count;
}

#endif
