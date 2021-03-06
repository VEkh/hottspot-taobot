#if !defined ETRADE__SPEEDOMETER_log_simple_moving_average
#define ETRADE__SPEEDOMETER_log_simple_moving_average

#include "etrade/deps.cpp"           // json
#include "simple_moving_average.cpp" // simple_moving_average
#include "speedometer.h"             // ETrade::Speedometer
#include <iostream>                  // std::cout, std::endl
#include <utility>                   // std::pair

void ETrade::Speedometer::log_simple_moving_average() {
  std::cout << fmt.underline;
  std::cout << "💲 Simple Moving Average" << std::endl;
  std::cout << fmt.reset << fmt.bold << fmt.magenta;

  std::pair<int, double> simple_moving_average_30 = simple_moving_average(30);

  std::cout << "30 Tick (" << simple_moving_average_30.first
            << "-Sec) Average ($): " << simple_moving_average_30.second
            << std::endl
            << std::endl;
}

#endif
