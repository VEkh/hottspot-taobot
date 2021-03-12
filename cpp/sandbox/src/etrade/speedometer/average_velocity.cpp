#if !defined ETRADE__SPEEDOMETER_average_velocity
#define ETRADE__SPEEDOMETER_average_velocity

#include "speedometer.h" // ETrade::Speedometer, quote_t, quotes_ptr
#include <utility>       // std::pair
#include <vector>        // std::vector

std::pair<int, double> ETrade::Speedometer::average_velocity(const int ticks) {
  std::vector<quote_t> quotes = *quotes_ptr;

  if (quotes.size() < ticks) {
    return std::pair<int, double>(0, 0);
  }

  const quote_t current_quote = quotes.back();
  const quote_t past_quote = quotes.at(quotes.size() - ticks);

  const double current_price = current_quote.current_price;
  const double current_timestamp = current_quote.timestamp;
  const double first_price = quotes.front().current_price;
  const double past_price = past_quote.current_price;
  const double past_timestamp = past_quote.timestamp;

  const int time_delta = current_timestamp - past_timestamp;
  const double velocity =
      100 * (((current_price - past_price) / first_price) / time_delta);

  return std::pair<int, double>(time_delta, velocity);
}

#endif
