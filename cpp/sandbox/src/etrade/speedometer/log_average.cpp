#if !defined ETRADE__SPEEDOMETER_log_average
#define ETRADE__SPEEDOMETER_log_average

#include "average_velocity.cpp" // average_velocity
#include "speedometer.h"        // ETrade::Speedometer
#include <iostream>             // std::cout, std::endl
#include <utility>              // std::pair

void ETrade::Speedometer::log_average(const int ticks) {
  const std::pair<int, double> velocity_pair = average_velocity(ticks);

  if (!velocity_pair.second) {
    return;
  }

  const char *tick_spacing = ticks < 10 ? "  " : " ";
  const char *velocity_units = " (%/s)";

  std::cout << ticks << tick_spacing << "Tick"
            << " (" << velocity_pair.first << "-Sec) Velocity" << velocity_units
            << ": " << velocity_pair.second << std::endl;
}

#endif
