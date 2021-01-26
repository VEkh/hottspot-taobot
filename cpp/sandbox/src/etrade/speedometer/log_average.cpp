#if !defined ETRADE__SPEEDOMETER_log_average
#define ETRADE__SPEEDOMETER_log_average

#include "speedometer.h" // ETrade::Speedometer, quotes_ptr
#include <iostream>      // std::cout, std::endl
#include <utility>       // std::pair

void ETrade::Speedometer::log_average(const int ticks) {
  const json quotes = *quotes_ptr;

  if (quotes.size() < ticks) {
    return;
  }

  const char *tick_spacing = ticks < 10 ? "  " : " ";
  const char *velocity_units = " (%/s)";
  const json current_quote = quotes.back();
  const json past_quote = quotes.at(quotes.size() - ticks);

  const double current_price = current_quote["currentPrice"];
  const double current_timestamp = current_quote["timestamp"];
  const double first_price = quotes.front()["currentPrice"];
  const double past_price = past_quote["currentPrice"];
  const double past_timestamp = past_quote["timestamp"];

  const int time_delta = current_timestamp - past_timestamp;
  const double average =
      ((current_price - past_price) / first_price) / time_delta;

  std::cout << ticks << tick_spacing << "Tick"
            << " (" << time_delta << "-Sec) Velocity" << velocity_units << ": "
            << average << std::endl;
}

#endif
