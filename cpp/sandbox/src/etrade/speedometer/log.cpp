#if !defined ETRADE__SPEEDOMETER_log
#define ETRADE__SPEEDOMETER_log

#include "lib/formatted.cpp"        // Formatted
#include "log_average_velocity.cpp" // log_average_velocity
#include "log_displacement.cpp"     // log_displacement
#include "speedometer.h"            // ETrade::Speedometer, stream_format
#include <iomanip>                  // std::setprecision
#include <iostream>                 // std::cout, std::endl, std::fixed

void ETrade::Speedometer::log() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << std::setprecision(6) << std::fixed;
  std::cout << fmt.bold << fmt.magenta << std::endl;

  std::cout << "⌚ Speedometer\n" << std::endl;

  std::cout << fmt.underline;
  std::cout << "📏 Displacement" << std::endl;
  std::cout << fmt.reset << fmt.bold << fmt.magenta;

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
