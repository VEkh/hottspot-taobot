#ifndef ALPACA__TAO_BOT_log_position
#define ALPACA__TAO_BOT_log_position

#include "alpaca/constants.cpp"   // Alpaca::constants
#include "is_position_closed.cpp" // is_position_closed
#include "lib/formatted.cpp"      // Formatted
#include "lib/utils/integer.cpp"  // utils::integer_
#include "lib/utils/string.cpp"   // ::utils::string
#include "order_duration.cpp"     // order_duration
#include "profit_percentage.cpp"  // profit_percentage
#include "tao_bot.h"              // Alpaca::TaoBot, fmt, order_action_t
#include <iostream>               // std::cout, std::endl
#include <stdio.h>                // printf

void Alpaca::TaoBot::log_position() {
  if (is_position_closed()) {
    std::cout << fmt.bold << fmt.cyan;
    puts("💀 No Open Positions.\n");
    std::cout << fmt.reset;

    return;
  }

  Formatted::Stream log_color =
      this->open_order_ptr->action == order_action_t::BUY ? fmt.green : fmt.red;

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s [%s]\n",
         ::utils::string::upcase(
             Alpaca::constants::ORDER_ACTIONS[this->open_order_ptr->action])
             .c_str(),
         this->open_order_ptr->symbol.c_str());
  std::cout << fmt.reset;

  std::cout << fmt.bold << log_color;
  printf(
      "Open   => Execution: %.2f • Profit: %.2f (%.2f%%) • Max Profit: %.2f\n",
      this->open_order_ptr->execution_price, this->open_order_ptr->profit,
      profit_percentage(this->open_order_ptr),
      this->open_order_ptr->max_profit);

  printf(
      "Close  => Execution: %.2f • Profit: %.2f (%.2f%%) • Max Profit: %.2f\n",
      this->close_order_ptr->execution_price, this->close_order_ptr->profit,
      profit_percentage(this->close_order_ptr),
      this->close_order_ptr->max_profit);

  printf("Status => Open: %s • Close: %s\n",
         ::utils::string::upcase(
             Alpaca::constants::ORDER_STATUSES[this->open_order_ptr->status])
             .c_str(),
         ::utils::string::upcase(
             Alpaca::constants::ORDER_STATUSES[this->close_order_ptr->status])
             .c_str());

  printf("Min Profit: %.2f • Max Loss: %.2f • Secure Profit (Lower): %.2f • "
         "Secure Profit (Upper): %.2f\n",
         this->exit_prices.min_profit, this->exit_prices.max_loss,
         this->exit_prices.lower_secure_profit,
         this->exit_prices.upper_secure_profit);

  printf("Quantity: %.5f\n", this->open_order_ptr->quantity);

  const int duration = order_duration(this->open_order_ptr);

  printf("Duration: %s\n",
         ::utils::integer_::seconds_to_clock(duration).c_str());

  std::cout << fmt.reset << std::endl;
}

#endif
