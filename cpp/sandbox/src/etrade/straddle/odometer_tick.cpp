#if !defined ETRADE__STRADDLE_odometer_tick
#define ETRADE__STRADDLE_odometer_tick

#include "straddle.h" // ETrade::Straddle, POLLING_INTERVAL_SECONDS, odometer
#include <cmath>      // abs

void ETrade::Straddle::odometer_tick(const double &previous_price,
                                     const double &current_price) {

  const double price_change = current_price - previous_price;

  const double current_velocity =
      (price_change / day_range) / POLLING_INTERVAL_SECONDS;

  const double last_velocity =
      odometer.velocities.empty() ? 0 : odometer.velocities.back();

  const double current_acceleration =
      (current_velocity - last_velocity) / POLLING_INTERVAL_SECONDS;

  odometer.accelerations.push_back(current_acceleration);
  odometer.velocities.push_back(current_velocity);
  odometer.momentum = abs(price_change / day_range) * current_velocity;
}

#endif
