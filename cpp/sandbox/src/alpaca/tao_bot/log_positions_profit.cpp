#ifndef ALPACA__TAO_BOT_log_positions_profit
#define ALPACA__TAO_BOT_log_positions_profit

#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/integer.cpp"    // utils::integer_
#include "max_loss_ratio.cpp"       // max_loss_ratio
#include "open_position_profit.cpp" // open_position_profit
#include "profit_duration.cpp"      // profit_duration
#include "take_profit_after.cpp"    // take_profit_after
#include "tao_bot.h"                // Alpaca::TaoBot, fmt
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf

void Alpaca::TaoBot::log_positions_profit() {
  const double profit = open_position_profit(this->open_order_ptr);

  this->open_order_ptr->max_position_profit =
      std::max(this->open_order_ptr->max_position_profit, profit);

  Formatted::Stream log_color = profit >= 0 ? fmt.green : fmt.red;

  std::cout << fmt.bold << log_color << fmt.underline;
  puts("💸 Position Profits");
  std::cout << fmt.reset;

  std::cout << fmt.bold << log_color;
  printf("Current: %.2f • Max: %.2f • Loss Duration: %s • Profit Duration: %s\n"
         "Max Loss Ratio %+.5f • Take Profit After (Sec): %i\n",
         profit, this->open_order_ptr->max_position_profit,
         ::utils::integer_::seconds_to_clock(
             profit_duration(this->loss_started_at))
             .c_str(),
         ::utils::integer_::seconds_to_clock(
             profit_duration(this->profit_started_at))
             .c_str(),
         max_loss_ratio(this->open_order_ptr),
         take_profit_after(this->open_order_ptr));
  std::cout << fmt.reset << std::endl;
}
#endif
