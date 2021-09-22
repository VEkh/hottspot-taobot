#ifndef ETRADE__TAO_BOT_log_position
#define ETRADE__TAO_BOT_log_position

/*
 * ETrade::TaoBot
 * fmt
 */
#include "tao_bot.h"

#include "etrade/constants.cpp"  // ETrade::constants
#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/float.cpp"   // utils::float
#include "profit_percentage.cpp" // profit_percentage
#include <iomanip>               // std::setprecision
#include <iostream>              // std::cout, std::endl, std::fixed
#include <stdio.h>               // printf
#include <time.h>                // time, time_t

void ETrade::TaoBot::log_position() {
  if (!this->open_order_ptr && !this->close_order_ptr) {
    std::cout << fmt.bold << fmt.cyan;
    std::cout << "💀 No Open Positions." << std::endl << std::endl;
    std::cout << fmt.reset;

    return;
  }

  time_t now;
  time(&now);
  const char *side = this->is_long_position ? "BUY" : "SELL_SHORT";
  Formatted::Stream log_color = this->is_long_position ? fmt.green : fmt.red;

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << fmt.bold << fmt.underline << log_color;
  std::cout << ETrade::constants::ORDER_ACTIONS[this->open_order.action]
            << std::endl;
  std::cout << fmt.reset;

  std::cout << fmt.bold << log_color;
  std::cout << "Open   => Execution: " << this->open_order.execution_price;
  std::cout << " • Profit: " << this->open_order.profit << " ("
            << profit_percentage(this->open_order_ptr) << "%)";
  std::cout << " • Max Profit: " << this->open_order.max_profit;
  std::cout << std::endl;

  std::cout << "Close  => Execution: " << this->close_order.execution_price;
  std::cout << " • Profit: " << this->close_order.profit << " ("
            << profit_percentage(this->close_order_ptr) << "%)";
  std::cout << std::endl;

  std::cout << "Status => Open: "
            << ETrade::constants::ORDER_STATUSES[this->open_order.status];
  std::cout << " • Close: "
            << ETrade::constants::ORDER_STATUSES[this->close_order.status];
  std::cout << std::endl;

  printf("Min Profit: %.2f • Max Loss: %.2f • Secure Profit (Lower): %.2f • "
         "Secure Profit (Upper): %.2f\n",
         this->exit_prices.min_profit, this->exit_prices.max_loss,
         this->exit_prices.secure_profit_lower,
         this->exit_prices.secure_profit_upper);

  if (this->open_order.max_profit_timestamp) {
    std::cout << "Max Profit ⌚ Δ: "
              << ::utils::integer_::seconds_to_clock(
                     now - this->open_order.max_profit_timestamp);
    std::cout << std::endl;
  }

  std::cout << "Quantity: " << this->quantity << std::endl;

  std::cout << fmt.reset << std::endl;
}

#endif
