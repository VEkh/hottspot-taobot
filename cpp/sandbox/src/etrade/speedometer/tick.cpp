#if !defined ETRADE__SPEEDOMETER_tick
#define ETRADE__SPEEDOMETER_tick

#include "etrade/deps.cpp" // json
#include "speedometer.h"   // ETrade::Speedometer, polling_interval, speedometer
#include <cmath>           // abs

void ETrade::Speedometer::tick(const json &quotes) {

  if (quotes.size() < 2) {
    return;
  }

  const json current_quote = quotes.back();
  const json previous_quote = *(quotes.end() - 2);
  const json reference_quote = quotes.front();

  const double current_price = current_quote["currentPrice"];
  const double previous_price = previous_quote["currentPrice"];
  const double reference_price = reference_quote["currentPrice"];

  const int current_timestamp = current_quote["timestamp"];
  const int previous_timestamp = previous_quote["timestamp"];
  const int time_change = current_timestamp - previous_timestamp;

  const double price_percent_change = current_price - previous_price;
  const double current_velocity = price_percent_change / time_change;
  const double last_velocity = velocities.empty() ? 0 : velocities.back();

  const double current_acceleration =
      (current_velocity - last_velocity) / time_change;

  accelerations.push_back(current_acceleration);
  velocities.push_back(current_velocity);
  momentum = abs(reference_price) * current_velocity;
}

#endif
