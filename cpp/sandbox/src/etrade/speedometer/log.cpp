#if !defined ETRADE__SPEEDOMETER_log
#define ETRADE__SPEEDOMETER_log

#include "speedometer.h" // ETrade::Speedometer, fmt
#include <iomanip>       // std::setprecision
#include <iostream>      // std::cout, std::endl, std::fixed

void ETrade::Speedometer::log() {
  std::cout << std::setprecision(6) << std::fixed;
  std::cout << fmt.bold << fmt.magenta << std::endl;

  std::cout << "⌚ Speedometer\n" << std::endl;

  std::cout << fmt.reset;
}

#endif
