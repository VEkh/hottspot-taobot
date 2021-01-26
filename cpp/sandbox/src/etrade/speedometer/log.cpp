#if !defined ETRADE__SPEEDOMETER_log
#define ETRADE__SPEEDOMETER_log

#include "lib/formatted.cpp" // Formatted
#include "log_average.cpp"   // log_average
#include "speedometer.h"     // ETrade::Speedometer, stream_format
#include <iomanip>           // std::setprecision
#include <iostream>          // std::cout, std::endl, std::fixed

void ETrade::Speedometer::log() {
  Formatted::fmt_stream_t fmt = stream_format;

  const char *displacement_units = "     (%)  ";
  const json quotes = *quotes_ptr;

  const double current_price = quotes.back()["currentPrice"];
  const double first_price = quotes.front()["currentPrice"];
  const double displacement = (current_price - first_price) / first_price;

  std::cout << std::setprecision(6) << std::fixed;
  std::cout << fmt.bold << fmt.magenta << std::endl;

  std::cout << "⌚ Speedometer: " << std::endl;
  std::cout << "Displacement        " << displacement_units << ": "
            << displacement << std::endl;

  log_average(5);
  log_average(10);
  log_average(30);
  log_average(60);
  log_average(2 * 60);
  log_average(5 * 60);
  log_average(10 * 60);
  log_average(15 * 60);
  log_average(20 * 60);
  log_average(30 * 60);

  std::cout << fmt.reset;
}

#endif
