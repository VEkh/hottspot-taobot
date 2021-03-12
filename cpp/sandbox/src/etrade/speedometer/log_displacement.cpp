#if !defined ETRADE__SPEEDOMETER_log_displacement
#define ETRADE__SPEEDOMETER_log_displacement

#include "average_displacement.cpp" // average_displacement
#include "speedometer.h"            // ETrade::Speedometer, quote_t
#include <iostream>                 // std::cout, std::endl
#include <utility>                  // std::pair
#include <vector>                   // std::vector

void ETrade::Speedometer::log_displacement() {
  std::cout << fmt.underline;
  std::cout << "📏 Displacement" << std::endl;
  std::cout << fmt.reset << fmt.bold << fmt.magenta;

  const std::vector<quote_t> quotes = *quotes_ptr;

  const double current_price = quotes.back().current_price;
  const double first_price = quotes.front().current_price;

  const double current_displacement = current_price - first_price;
  const double current_displacement_percent =
      100 * (current_displacement / first_price);

  std::cout << "Current (%): " << current_displacement_percent << std::endl;
  std::cout << "Current ($): " << current_displacement << std::endl;

  std::pair<int, double> average_displacement_45 = average_displacement(45);

  std::cout << "45 Tick (" << average_displacement_45.first
            << "-Sec) Average ($): " << average_displacement_45.second
            << std::endl;
}

#endif
