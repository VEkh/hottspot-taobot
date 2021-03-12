#if !defined ETRADE__STOCK_BOT_simple_moving_average
#define ETRADE__STOCK_BOT_simple_moving_average

#include "stock_bot.h" // ETrade::StockBot, quote_t, quotes
#include <utility>     // std::pair
#include <vector>      // std::vector

std::pair<int, double>
ETrade::StockBot::simple_moving_average(const int seconds) {
  std::pair<int, double> emtpy_average = {0, 0};

  if (quotes.empty()) {
    return emtpy_average;
  }

  const quote_t current_quote = quotes.back();
  quote_t past_quote = quotes.front();

  if (current_quote.timestamp - past_quote.timestamp < seconds) {
    return emtpy_average;
  }

  const int quotes_length = quotes.size();
  double sum = 0;
  int ticks;
  std::vector<quote_t>::reverse_iterator it = quotes.rbegin();

  for (ticks = 0; ticks < quotes_length; ticks++) {
    sum += it->current_price;

    if (current_quote.timestamp - it->timestamp >= seconds) {
      past_quote = *it;
      ticks++;
      break;
    }

    it++;
  }

  const double average = sum / ticks;
  const int time_delta = current_quote.timestamp - past_quote.timestamp;

  return std::pair<int, double>(time_delta, average);
}

#endif
