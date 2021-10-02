#ifndef ETRADE__TAO_BOT_log_position
#define ETRADE__TAO_BOT_log_position

#include "etrade/constants.cpp"  // ETrade::constants
#include "lib/formatted.cpp"     // Formatted
#include "profit_percentage.cpp" // profit_percentage
#include "tao_bot.h"             // ETrade::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void ETrade::TaoBot::log_position() {
  if (!this->open_order_ptr && !this->close_order_ptr) {
    std::cout << fmt.bold << fmt.cyan;
    puts("💀 No Open Positions.\n");
    std::cout << fmt.reset;

    return;
  }

  Formatted::Stream log_color = this->is_long_position ? fmt.green : fmt.red;

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s\n", ETrade::constants::ORDER_ACTIONS[this->open_order.action]);
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
         ETrade::constants::ORDER_STATUSES[this->open_order.status],
         ETrade::constants::ORDER_STATUSES[this->close_order.status]);

  printf("Min Profit: %.2f • Max Loss: %.2f • Secure Profit: %.2f\n",
         this->exit_prices.min_profit, this->exit_prices.max_loss,
         this->exit_prices.secure_profit);

  printf("Quantity: %i\n", this->quantity);

  std::cout << fmt.reset << std::endl;
}

#endif
