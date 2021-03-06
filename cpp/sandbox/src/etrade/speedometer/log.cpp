#if !defined ETRADE__SPEEDOMETER_log
#define ETRADE__SPEEDOMETER_log

#include "log_average_velocity.cpp"      // log_average_velocity
#include "log_displacement.cpp"          // log_displacement
#include "log_simple_moving_average.cpp" // log_simple_moving_average
#include "speedometer.h"                 // ETrade::Speedometer, fmt
#include <iomanip>                       // std::setprecision
#include <iostream>                      // std::cout, std::endl, std::fixed

void ETrade::Speedometer::log() {
  std::cout << std::setprecision(6) << std::fixed;
  std::cout << fmt.bold << fmt.magenta << std::endl;

  std::cout << "⌚ Speedometer\n" << std::endl;

  log_simple_moving_average();
  log_displacement();

  std::cout << fmt.underline << std::endl;
  std::cout << "💨 Velocity" << std::endl;
  std::cout << fmt.reset << fmt.bold << fmt.magenta;

  log_average_velocity(10);
  log_average_velocity(30);
  log_average_velocity(60);

  std::cout << fmt.reset;
}

#endif
