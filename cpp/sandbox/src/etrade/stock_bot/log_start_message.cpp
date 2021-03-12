#if !defined ETRADE__STOCK_BOT_log_start_message
#define ETRADE__STOCK_BOT_log_start_message

#include "stock_bot.h" // ETrade::StockBot, fmt, quantity, symbol
#include <iostream>         // std::cout, std::endl

void ETrade::StockBot::log_start_message() {
  std::cout << fmt.bold << fmt.cyan;
  std::cout << "Trading " << fmt.blue << quantity << fmt.cyan << " share(s) of "
            << fmt.blue << symbol << std::endl
            << std::endl;
  std::cout << fmt.reset;
}

#endif
