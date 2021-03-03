#if !defined ETRADE__SPEEDOMETER_average_displacement
#define ETRADE__SPEEDOMETER_average_displacement

#include "etrade/deps.cpp" // json
#include "speedometer.h"   // ETrade::Speedometer, quotes_ptr
#include <utility>         // std::pair

std::pair<int, double>
ETrade::Speedometer::average_displacement(const int ticks) {
  json quotes = *quotes_ptr;

  if (quotes.size() < ticks) {
    return std::pair<int, double>(0, 0);
  }

  const double first_price = quotes.front()["currentPrice"];
  double sum = 0;
  json::reverse_iterator it = quotes.rbegin();

  for (int i = 0; i < ticks; i++) {
    const double tick_price = it->at("currentPrice");
    const double displacement = tick_price - first_price;

    sum += displacement;

    it++;
  }

  const double average_displacement = sum / ticks;

  const json current_quote = quotes.back();
  const json past_quote = quotes.at(quotes.size() - ticks);

  const double current_timestamp = current_quote["timestamp"];
  const double past_timestamp = past_quote["timestamp"];
  const int time_delta = current_timestamp - past_timestamp;

  return std::pair<int, double>(time_delta, average_displacement);
}

#endif
