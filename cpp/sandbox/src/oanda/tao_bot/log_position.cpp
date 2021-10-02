#ifndef OANDA__TAO_BOT_log_position
#define OANDA__TAO_BOT_log_position

#include "lib/formatted.cpp"     // Formatted
#include "oanda/constants.cpp"   // Oanda::constants
#include "profit_percentage.cpp" // profit_percentage
#include "tao_bot.h"             // Oanda::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Oanda::TaoBot::log_position() {
  if (!this->open_order_ptr && !this->close_order_ptr) {
    std::cout << fmt.bold << fmt.cyan;
    puts("💀 No Open Positions.\n");
    std::cout << fmt.reset;

    return;
  }

  Formatted::Stream log_color = this->is_long_position ? fmt.green : fmt.red;

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s\n", Oanda::constants::ORDER_ACTIONS[this->open_order.action]);
  std::cout << fmt.reset;

  std::cout << fmt.bold << log_color;
  printf(
      "Open   => Execution: %.5f • Profit: %.5f (%.2f%%) • Max Profit: %.5f\n",
      this->open_order.execution_price, this->open_order.profit,
      profit_percentage(this->open_order_ptr), this->open_order.max_profit);

  printf(
      "Close  => Execution: %.5f • Profit: %.5f (%.2f%%) • Max Profit: %.5f\n",
      this->close_order.execution_price, this->close_order.profit,
      profit_percentage(this->close_order_ptr), this->close_order.max_profit);

  printf("Status => Open: %s • Close: %s\n",
         Oanda::constants::ORDER_STATUSES[this->open_order.status],
         Oanda::constants::ORDER_STATUSES[this->close_order.status]);

  printf("Min Profit: %.5f • Max Loss: %.5f • Secure Profit: %.5f\n",
         this->exit_prices.min_profit, this->exit_prices.max_loss,
         this->exit_prices.secure_profit);

  printf("Quantity: %i\n", this->quantity);

  std::cout << fmt.reset << std::endl;
}

#endif
