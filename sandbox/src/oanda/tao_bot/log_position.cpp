#ifndef OANDA__TAO_BOT_log_position
#define OANDA__TAO_BOT_log_position

#include "is_position_closed.cpp"   // is_position_closed
#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/integer.cpp"    // utils::integer_
#include "lib/utils/string.cpp"     // ::utils::string
#include "lib/utils/time.cpp"       // ::utils::time_
#include "oanda/constants.cpp"      // Oanda::constants
#include "open_position_profit.cpp" // open_position_profit
#include "order_duration.cpp"       // order_duration
#include "profit_percentage.cpp"    // profit_percentage
#include "tao_bot.h"                // Oanda::TaoBot, fmt, order_action_t
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf

void Oanda::TaoBot::log_position() {
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
             Oanda::constants::ORDER_ACTIONS[this->open_order_ptr->action])
             .c_str(),
         this->open_order_ptr->symbol.c_str());
  std::cout << fmt.reset;

  std::cout << fmt.bold << log_color;
  printf("Open   => Execution: %'.5f @ %s • Profit    : %+'.5f (%+.2f%%)\n",
         this->open_order_ptr->execution_price,
         ::utils::time_::date_string(this->open_order_ptr->timestamp,
                                     "%m/%d %R %Z", "America/Chicago")
             .c_str(),
         this->open_order_ptr->profit,
         profit_percentage(this->open_order_ptr, "profit"));

  printf("                                           Max Profit: %+'.5f "
         "(%+.2f%%) @ "
         "%s%s\n",
         this->open_order_ptr->max_profit,
         profit_percentage(this->open_order_ptr, "max_profit"),
         ::utils::time_::date_string(this->open_order_ptr->max_profit_at,
                                     "%m/%d %R %Z", "America/Chicago")
             .c_str(),
         this->open_order_ptr->profit == this->open_order_ptr->max_profit ? " 🔥"
                                                                          : "");

  printf("                                           Min Profit: %+'.5f "
         "(%+.2f%%) @ "
         "%s%s\n",
         this->open_order_ptr->min_profit,
         profit_percentage(this->open_order_ptr, "min_profit"),
         ::utils::time_::date_string(this->open_order_ptr->min_profit_at,
                                     "%m/%d %R %Z", "America/Chicago")
             .c_str(),
         this->open_order_ptr->profit == this->open_order_ptr->min_profit ? " 💦"
                                                                          : "");

  if (this->close_order_ptr->execution_price) {
    printf("Close  => Execution: %'.5f • Profit: %'.5f (%.2f%%)\n",
           this->close_order_ptr->execution_price,
           this->close_order_ptr->profit,
           profit_percentage(this->close_order_ptr));
  }

  printf("Status => Open: %s • Close: %s\n",
         ::utils::string::upcase(
             Oanda::constants::ORDER_STATUSES[this->open_order_ptr->status])
             .c_str(),
         ::utils::string::upcase(
             Oanda::constants::ORDER_STATUSES[this->close_order_ptr->status])
             .c_str());

  const double asset_deficit =
      this->performance.current_balance - this->performance.max_balance;

  const double unit_deficit = asset_deficit / this->open_order_ptr->quantity;

  printf("Stop Profit: %'.5f • Stop Loss: %'.5f • "
         "Unit Deficit: %'.5f\n",
         this->exit_prices.stop_profit, this->exit_prices.stop_loss,
         unit_deficit);

  printf("Quantity: %'.5i\n", this->open_order_ptr->quantity);

  const int duration = order_duration(this->open_order_ptr);
  const int max_profit_duration =
      order_duration(this->open_order_ptr, "max_profit");
  const int min_profit_duration =
      order_duration(this->open_order_ptr, "min_profit");

  printf("Duration: %s • Max Profit Duration: %s • Min Profit Duration: %s\n",
         ::utils::integer_::seconds_to_clock(duration).c_str(),
         ::utils::integer_::seconds_to_clock(max_profit_duration).c_str(),
         ::utils::integer_::seconds_to_clock(min_profit_duration).c_str());

  std::cout << fmt.reset << std::endl;

  const double position_profit = open_position_profit(this->open_order_ptr);

  log_color = position_profit >= 0 ? fmt.green : fmt.red;

  std::cout << fmt.bold << log_color << fmt.underline;
  printf("💸 Position Profit");
  std::cout << fmt.reset << std::endl;

  std::cout << fmt.bold << log_color;
  printf("Current: %'.5f • Max: %'.5f\n", position_profit,
         this->open_order_ptr->max_position_profit);
  std::cout << fmt.reset << std::endl;
}

#endif
