#ifndef OANDA__TAO_BOT_build_moving_buy_sell_ratio_average
#define OANDA__TAO_BOT_build_moving_buy_sell_ratio_average

#include "tao_bot.h" // Oanda::TaoBot, quote_t
#include <algorithm> // std::max
#include <map>       // std::map
#include <math.h>    // abs
#include <vector>    // std::vector

std::map<int, std::map<const char *, double>>
Oanda::TaoBot::build_moving_buy_sell_ratio_average(std::vector<int> &periods) {
  const quote_t current_quote = this->quotes.back();
  const quote_t first_quote = this->quotes.front();

  double buy_delta = 0.00;
  double sell_delta = 0.00;
  int max_period = 0;
  std::map<int, std::map<const char *, double>> out;
  std::map<int, std::map<const char *, double>> period_map;

  for (int period : periods) {
    period_map[period] = {{"buy_delta", 0}, {"sell_delta", 0}};
    out[period] = {{"buy", 0}, {"sell", 0}};
    max_period = std::max(max_period, period);
  }

  if ((current_quote.timestamp - first_quote.timestamp) <= max_period) {
    return out;
  }

  std::vector<quote_t>::reverse_iterator it = this->quotes.rbegin();

  while (it != this->quotes.rend() &&
         (current_quote.timestamp - it->timestamp) <= max_period) {

    const double price_delta = it->price - ((it + 1)->price);

    for (int period : periods) {
      if ((current_quote.timestamp - it->timestamp) > period) {
        continue;
      }

      if (price_delta > 0) {
        period_map[period]["buy_delta"] += price_delta;
      } else if (price_delta < 0) {
        period_map[period]["sell_delta"] += price_delta;
      }
    }

    it++;
  }

  for (int period : periods) {
    double average_buy_sell_ratio =
        abs(period_map[period]["buy_delta"] / period_map[period]["sell_delta"]);

    double average_sell_buy_ratio = 1 / average_buy_sell_ratio;

    out[period] = {
        {"buy", average_buy_sell_ratio},
        {"sell", average_sell_buy_ratio},
    };
  }

  return out;
}

#endif
