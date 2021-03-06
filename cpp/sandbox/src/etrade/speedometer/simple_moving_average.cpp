#if !defined ETRADE__SPEEDOMETER_simple_moving_average
#define ETRADE__SPEEDOMETER_simple_moving_average

#include "etrade/deps.cpp" // json
#include "speedometer.h"   // ETrade::Speedometer, quotes_ptr
#include <utility>         // std::pair

std::pair<int, double>
ETrade::Speedometer::simple_moving_average(const int ticks) {
  json quotes = *quotes_ptr;

  if (quotes.size() < ticks) {
    return std::pair<int, double>(0, 0);
  }

  double sum = 0;
  json::reverse_iterator it = quotes.rbegin();

  for (int i = 0; i < ticks; i++) {
    const double tick_price = it->at("currentPrice");
    sum += tick_price;
    it++;
  }

  const double average = sum / ticks;

  const json current_quote = quotes.back();
  const json past_quote = quotes.at(quotes.size() - ticks);

  const double current_timestamp = current_quote["timestamp"];
  const double past_timestamp = past_quote["timestamp"];
  const int time_delta = current_timestamp - past_timestamp;

  return std::pair<int, double>(time_delta, average);
}

#endif
