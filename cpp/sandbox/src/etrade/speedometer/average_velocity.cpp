#if !defined ETRADE__SPEEDOMETER_average_velocity
#define ETRADE__SPEEDOMETER_average_velocity

#include "etrade/deps.cpp" // json
#include "speedometer.h"   // ETrade::Speedometer, quotes_ptr
#include <utility>         // std::pair

std::pair<int, double> ETrade::Speedometer::average_velocity(const int ticks) {
  const json quotes = *quotes_ptr;

  if (quotes.size() < ticks) {
    return std::pair<int, double>(0, 0);
  }

  const json current_quote = quotes.back();
  const json past_quote = quotes.at(quotes.size() - ticks);

  const double current_price = current_quote["currentPrice"];
  const double current_timestamp = current_quote["timestamp"];
  const double first_price = quotes.front()["currentPrice"];
  const double past_price = past_quote["currentPrice"];
  const double past_timestamp = past_quote["timestamp"];

  const int time_delta = current_timestamp - past_timestamp;
  const double velocity =
      100 * (((current_price - past_price) / first_price) / time_delta);

  return std::pair<int, double>(time_delta, velocity);
}

#endif
