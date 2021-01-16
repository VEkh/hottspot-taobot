#if !defined ETRADE__SPEEDOMETER_log
#define ETRADE__SPEEDOMETER_log

#include "compute_average.cpp" // compute_average
#include "lib/formatted.cpp"   // Formatted
#include "speedometer.h"       // ETrade::Speedometer, stream_format
#include <iomanip>             // std::setprecision
#include <iostream>            // std::cout, std::endl, std::fixed

void ETrade::Speedometer::log() {
  Formatted::fmt_stream_t fmt = stream_format;

  const double current_acceleration =
      accelerations.empty() ? 0 : accelerations.back();
  const double current_velocity = velocities.empty() ? 0 : velocities.back();
  const char *acceleration_units = " ($/s^2)";
  const char *momentum_units = " ($^2/s)";
  const char *velocity_units = " ($/s)  ";

  std::cout << std::setprecision(6) << std::fixed;
  std::cout << fmt.bold << fmt.magenta << std::endl;

  std::cout << "⌚ Speedometer: " << std::endl;
  std::cout << "Current Acceleration   " << acceleration_units << ": "
            << current_acceleration << std::endl;
  std::cout << "Current Velocity       " << velocity_units << ": "
            << current_velocity << std::endl;
  std::cout << "Momentum               " << momentum_units << ": " << momentum
            << std::endl
            << std::endl;

  std::cout << "Avg 5  Sec Acceleration" << acceleration_units << ": "
            << compute_average(accelerations, 5) << std::endl;

  std::cout << "Avg 10 Sec Acceleration" << acceleration_units << ": "
            << compute_average(accelerations, 10) << std::endl;

  std::cout << "Avg 15 Sec Acceleration" << acceleration_units << ": "
            << compute_average(accelerations, 15) << std::endl;

  std::cout << "Avg 30 Sec Acceleration" << acceleration_units << ": "
            << compute_average(accelerations, 30) << std::endl;

  std::cout << "Avg 60 Sec Acceleration" << acceleration_units << ": "
            << compute_average(accelerations, 60) << std::endl
            << std::endl;

  std::cout << "Avg 5  Sec Velocity    " << velocity_units << ": "
            << compute_average(velocities, 5) << std::endl;

  std::cout << "Avg 10 Sec Velocity    " << velocity_units << ": "
            << compute_average(velocities, 10) << std::endl;

  std::cout << "Avg 15 Sec Velocity    " << velocity_units << ": "
            << compute_average(velocities, 15) << std::endl;

  std::cout << "Avg 30 Sec Velocity    " << velocity_units << ": "
            << compute_average(velocities, 30) << std::endl;

  std::cout << "Avg 60 Sec Velocity    " << velocity_units << ": "
            << compute_average(velocities, 60) << std::endl;

  std::cout << fmt.reset;
}

#endif
