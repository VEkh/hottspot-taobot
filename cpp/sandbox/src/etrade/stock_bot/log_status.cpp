#if !defined ETRADE__STOCK_BOT_log_status
#define ETRADE__STOCK_BOT_log_status

#include "lib/formatted.cpp" // Formatted
#include "status.cpp"        // status
#include "stock_bot.h"       // ETrade::StockBot, status_t
#include <iostream>          // std::cout, std::endl

void ETrade::StockBot::log_status() {
  Formatted::fmt_stream_t fmt = stream_format;

  if (status() == status_t::LIMBO) {
    std::cout << fmt.yellow << std::endl;
    std::cout << "👻 This position is in limbo. Consider opening another one."
              << std::endl;
    std::cout << fmt.reset;
  }
}

#endif
