#ifndef ALPACA__PERFORMANCE_LOGGER_sign_char
#define ALPACA__PERFORMANCE_LOGGER_sign_char

#include "performance_logger.h" // PerformanceLogger

char Alpaca::PerformanceLogger::sign_char(const double n) {
  return n >= 0 ? '+' : '-';
};

#endif
