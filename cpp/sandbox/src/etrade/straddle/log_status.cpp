#if !defined ETRADE__STRADDLE_log_status
#define ETRADE__STRADDLE_log_status

#include "lib/formatted.cpp" // Formatted
#include "status.cpp"        // status
#include "straddle.h"        // ETrade::Straddle, status_t
#include <iostream>          // std::cout, std::endl

void ETrade::Straddle::log_status() {
  Formatted::fmt_stream_t fmt = stream_format;

  if (status() == status_t::LIMBO) {
    std::cout << fmt.yellow << std::endl;
    std::cout << "👻 This position is in limbo. Consider opening another one."
              << std::endl;
    std::cout << fmt.reset;
  }
}

#endif
