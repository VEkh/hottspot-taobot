#if !defined ETRADE__SPEEDOMETER_tick
#define ETRADE__SPEEDOMETER_tick

#include "speedometer.h" // ETrade::Speedometer, polling_interval, speedometer
#include <cmath>         // abs

void ETrade::Speedometer::tick(const double &previous_price,
                               const double &current_price) {

  const double price_change = current_price - previous_price;

  const double current_velocity = price_change / polling_interval;

  const double last_velocity = velocities.empty() ? 0 : velocities.back();

  const double current_acceleration =
      (current_velocity - last_velocity) / polling_interval;

  accelerations.push_back(current_acceleration);
  velocities.push_back(current_velocity);
  momentum = abs(price_change) * current_velocity;
}

#endif
