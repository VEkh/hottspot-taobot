#if !defined ETRADE__STOCK_BOT_compute_moving_buy_sell_ratio_average
#define ETRADE__STOCK_BOT_compute_moving_buy_sell_ratio_average

#include "stock_bot.h" // ETrade::StockBot, quote_t
#include <algorithm>   // std::max
#include <map>         // std::map
#include <vector>      // std::vector

std::map<int, std::map<const char *, double>>
ETrade::StockBot::compute_moving_buy_sell_ratio_average(
    std::vector<int> &periods) {
  const quote_t current_quote = this->quotes.back();
  const quote_t first_quote = this->quotes.front();

  int max_period = 0;
  std::map<int, std::map<const char *, double>> out;
  std::map<int, std::map<const char *, double>> period_map;

  for (int period : periods) {
    period_map[period] = {{"count", 0}, {"total", 0}};
    out[period] = {{"buy", 0}, {"sell", 0}};
    max_period = std::max(max_period, period);
  }

  if ((current_quote.timestamp - first_quote.timestamp) <= max_period) {
    return out;
  }

  std::vector<quote_t>::reverse_iterator it = this->quotes.rbegin();

  while (it != this->quotes.rend() &&
         (current_quote.timestamp - it->timestamp) <= max_period) {
    if (!it->simple_moving_average.buy_sell_ratio) {
      return out;
    }

    for (int period : periods) {
      if ((current_quote.timestamp - it->timestamp) <= period) {
        period_map[period]["count"]++;
        period_map[period]["total"] += it->simple_moving_average.buy_sell_ratio;
      }
    }

    it++;
  }

  for (int period : periods) {
    double average_buy_sell_ratio =
        period_map[period]["total"] / period_map[period]["count"];

    double average_sell_buy_ratio =
        !!average_buy_sell_ratio ? 1 / average_buy_sell_ratio : 0;

    out[period] = {
        {"buy", average_buy_sell_ratio},
        {"sell", average_sell_buy_ratio},
    };
  }

  return out;
}

#endif
