#ifndef ALPACA__TAO_BOT_log_position
#define ALPACA__TAO_BOT_log_position

#include "alpaca/constants.cpp"  // Alpaca::constants
#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/string.cpp"  // ::utils::string
#include "profit_percentage.cpp" // profit_percentage
#include "tao_bot.h"             // Alpaca::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Alpaca::TaoBot::log_position() {
  if (!this->open_order_ptr && !this->close_order_ptr) {
    std::cout << fmt.bold << fmt.cyan;
    puts("💀 No Open Positions.\n");
    std::cout << fmt.reset;

    return;
  }

  Formatted::Stream log_color = this->is_long_position ? fmt.green : fmt.red;

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s\n", ::utils::string::upcase(
                     Alpaca::constants::ORDER_ACTIONS[this->open_order.action])
                     .c_str());
  std::cout << fmt.reset;

  std::cout << fmt.bold << log_color;
  printf(
      "Open   => Execution: %.2f • Profit: %.2f (%.2f%%) • Max Profit: %.2f\n",
      this->open_order.execution_price, this->open_order.profit,
      profit_percentage(this->open_order_ptr), this->open_order.max_profit);

  printf(
      "Close  => Execution: %.2f • Profit: %.2f (%.2f%%) • Max Profit: %.2f\n",
      this->close_order.execution_price, this->close_order.profit,
      profit_percentage(this->close_order_ptr), this->close_order.max_profit);

  printf("Status => Open: %s • Close: %s\n",
         ::utils::string::upcase(
             Alpaca::constants::ORDER_STATUSES[this->open_order.status])
             .c_str(),
         ::utils::string::upcase(
             Alpaca::constants::ORDER_STATUSES[this->close_order.status])
             .c_str());

  printf("Min Profit: %.2f • Max Loss: %.2f • Secure Profit (Lower): %.2f • "
         "Secure Profit (Upper): %.2f\n",
         this->exit_prices.min_profit, this->exit_prices.max_loss,
         this->exit_prices.lower_secure_profit,
         this->exit_prices.upper_secure_profit);

  printf("Quantity: %.5f\n", this->quantity);

  std::cout << fmt.reset << std::endl;
}

#endif
