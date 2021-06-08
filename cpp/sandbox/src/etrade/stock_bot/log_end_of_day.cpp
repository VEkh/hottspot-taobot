#ifndef ETRADE__STOCK_BOT_log_end_of_day
#define ETRADE__STOCK_BOT_log_end_of_day

/*
 * ETrade::StockBot
 * etrade_client
 * fmt
 */
#include "stock_bot.h"

#include "lib/utils/time.cpp" // utils::time_
#include <iostream>           // std::cout, std::endl

void ETrade::StockBot::log_end_of_day() {
  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "🎊 The day's over! Hope you made some guap 🤑" << std::endl;
  std::cout << fmt.reset;
}

#endif
