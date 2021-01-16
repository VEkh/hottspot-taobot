#if !defined ETRADE__STRADDLE_log_odometer
#define ETRADE__STRADDLE_log_odometer

#include "compute_odometer_average.cpp" // compute_odometer_average
#include "lib/formatted.cpp"            // Formatted
#include "straddle.h" // ETrade::Straddle, POLLING_INTERVAL_SECONDS, stream_format
#include <iomanip>    // std::setprecision
#include <iostream>   // std::cout, std::endl, std::fixed

void ETrade::Straddle::log_odometer() {
  Formatted::fmt_stream_t fmt = stream_format;

  const double current_acceleration =
      odometer.accelerations.empty() ? 0 : odometer.accelerations.back();
  const double current_velocity =
      odometer.velocities.empty() ? 0 : odometer.velocities.back();
  const char *acceleration_units = " (day range/s^2)";
  const char *momentum_units = " (day range^2/s)  ";
  const char *velocity_units = " (day range/s)";

  std::cout << std::setprecision(6) << std::fixed;
  std::cout << fmt.bold << fmt.magenta << std::endl;

  std::cout << "⌚ Odometer: " << std::endl;
  std::cout << "Current Acceleration   " << acceleration_units << ": "
            << current_acceleration << std::endl;
  std::cout << "Current Velocity       " << velocity_units << ": "
            << current_velocity << std::endl;
  std::cout << "Momentum               " << momentum_units << ": "
            << odometer.momentum << std::endl
            << std::endl;

  std::cout << "Avg 5  Sec Acceleration" << acceleration_units << ": "
            << compute_odometer_average(odometer.accelerations, 5) << std::endl;

  std::cout << "Avg 10 Sec Acceleration" << acceleration_units << ": "
            << compute_odometer_average(odometer.accelerations, 10)
            << std::endl;

  std::cout << "Avg 15 Sec Acceleration" << acceleration_units << ": "
            << compute_odometer_average(odometer.accelerations, 15)
            << std::endl;

  std::cout << "Avg 30 Sec Acceleration" << acceleration_units << ": "
            << compute_odometer_average(odometer.accelerations, 30)
            << std::endl;

  std::cout << "Avg 60 Sec Acceleration" << acceleration_units << ": "
            << compute_odometer_average(odometer.accelerations, 60) << std::endl
            << std::endl;

  std::cout << "Avg 5  Sec Velocity    " << velocity_units << ": "
            << compute_odometer_average(odometer.velocities, 5) << std::endl;

  std::cout << "Avg 10 Sec Velocity    " << velocity_units << ": "
            << compute_odometer_average(odometer.velocities, 10) << std::endl;

  std::cout << "Avg 15 Sec Velocity    " << velocity_units << ": "
            << compute_odometer_average(odometer.velocities, 15) << std::endl;

  std::cout << "Avg 30 Sec Velocity    " << velocity_units << ": "
            << compute_odometer_average(odometer.velocities, 30) << std::endl;

  std::cout << "Avg 60 Sec Velocity    " << velocity_units << ": "
            << compute_odometer_average(odometer.velocities, 60) << std::endl;

  std::cout << fmt.reset;
}

#endif
