#if !defined ETRADE__SPEEDOMETER_log_displacement
#define ETRADE__SPEEDOMETER_log_displacement

#include "average_displacement.cpp" // average_displacement
#include "etrade/deps.cpp"          // json
#include "speedometer.h"            // ETrade::Speedometer
#include <iostream>                 // std::cout, std::endl
#include <utility>                  // std::pair

void ETrade::Speedometer::log_displacement() {
  std::cout << fmt.underline;
  std::cout << "📏 Displacement" << std::endl;
  std::cout << fmt.reset << fmt.bold << fmt.magenta;

  const json quotes = *quotes_ptr;

  const double current_price = quotes.back()["currentPrice"];
  const double first_price = quotes.front()["currentPrice"];

  const double current_displacement = current_price - first_price;
  const double current_displacement_percent =
      100 * (current_displacement / first_price);

  std::cout << "Current (%): " << current_displacement_percent << std::endl;
  std::cout << "Current ($): " << current_displacement << std::endl;

  std::pair<int, double> average_displacement_30 = average_displacement(30);

  std::cout << "30 Tick (" << average_displacement_30.first
            << "-Sec) Average ($): " << average_displacement_30.second
            << std::endl;
}

#endif
