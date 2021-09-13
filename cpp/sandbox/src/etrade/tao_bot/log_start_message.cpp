#ifndef ETRADE__TAO_BOT_log_start_message
#define ETRADE__TAO_BOT_log_start_message

#include "tao_bot.h" // ETrade::TaoBot, fmt, quantity, symbol
#include <iostream>    // std::cout, std::endl

void ETrade::TaoBot::log_start_message() {
  std::cout << fmt.bold << fmt.cyan;
  std::cout << "Trading " << fmt.blue << quantity << fmt.cyan << " share(s) of "
            << fmt.blue << symbol << std::endl
            << std::endl;
  std::cout << fmt.reset;
}

#endif
