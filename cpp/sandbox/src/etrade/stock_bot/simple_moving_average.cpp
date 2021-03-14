#if !defined ETRADE__STOCK_BOT_simple_moving_average
#define ETRADE__STOCK_BOT_simple_moving_average

#include "stock_bot.h" // ETrade::StockBot, quote_t, quotes
#include <utility>     // std::pair
#include <vector>      // std::vector

ETrade::StockBot::sma_t
ETrade::StockBot::simple_moving_average(const int seconds) {
  sma_t emtpy_average;

  if (quotes.empty()) {
    return emtpy_average;
  }

  const quote_t current_quote = quotes.back();
  quote_t past_quote = quotes.front();

  if (current_quote.timestamp - past_quote.timestamp < seconds) {
    return emtpy_average;
  }

  const int quotes_length = quotes.size();
  double buy_delta = 0.00;
  double sell_delta = 0.00;
  double total_price = 0;
  int ticks;
  std::vector<quote_t>::reverse_iterator it = quotes.rbegin();

  for (ticks = 1; ticks < quotes_length; ticks++) {
    total_price += it->current_price;

    if (it != quotes.rend()) {
      const double price_delta = it->current_price - (it + 1)->current_price;

      if (price_delta > 0) {
        buy_delta += price_delta;
      } else if (price_delta < 0) {
        sell_delta += price_delta;
      }
    }

    if (current_quote.timestamp - it->timestamp >= seconds) {
      past_quote = *it;
      break;
    }

    it++;
  }

  const double average = total_price / ticks;
  const int seconds_delta = current_quote.timestamp - past_quote.timestamp;

  return {
      .buy_delta = buy_delta,
      .price = average,
      .seconds = seconds_delta,
      .sell_delta = sell_delta,
  };
}

#endif
