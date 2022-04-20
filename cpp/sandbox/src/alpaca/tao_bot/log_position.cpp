#ifndef ALPACA__TAO_BOT_log_position
#define ALPACA__TAO_BOT_log_position

#include "alpaca/constants.cpp"  // Alpaca::constants
#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/integer.cpp" // utils::integer_
#include "lib/utils/string.cpp"  // ::utils::string
#include "order_duration.cpp"    // order_duration
#include "profit_percentage.cpp" // profit_percentage
#include "tao_bot.h"             // Alpaca::TaoBot, fmt, order_action_t
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Alpaca::TaoBot::log_position(const order_t *close_order_ptr_,
                                  const order_t *open_order_ptr_,
                                  const char *label = "") {
  if (!close_order_ptr_ || !open_order_ptr_) {
    return;
  }

  Formatted::Stream log_color =
      open_order_ptr_->action == order_action_t::BUY ? fmt.green : fmt.red;

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s [%s]%s\n",
         ::utils::string::upcase(
             Alpaca::constants::ORDER_ACTIONS[open_order_ptr_->action])
             .c_str(),
         open_order_ptr_->symbol.c_str(), label);
  std::cout << fmt.reset;

  std::cout << fmt.bold << log_color;
  printf(
      "Open   => Execution: %.2f • Profit: %.2f (%.2f%%) • Max Profit: %.2f\n",
      open_order_ptr_->execution_price, open_order_ptr_->profit,
      profit_percentage(open_order_ptr_), open_order_ptr_->max_profit);

  printf(
      "Close  => Execution: %.2f • Profit: %.2f (%.2f%%) • Max Profit: %.2f\n",
      close_order_ptr_->execution_price, close_order_ptr_->profit,
      profit_percentage(close_order_ptr_), close_order_ptr_->max_profit);

  printf("Status => Open: %s • Close: %s\n",
         ::utils::string::upcase(
             Alpaca::constants::ORDER_STATUSES[open_order_ptr_->status])
             .c_str(),
         ::utils::string::upcase(
             Alpaca::constants::ORDER_STATUSES[close_order_ptr_->status])
             .c_str());

  printf("Min Profit: %.2f • Max Loss: %.2f • Secure Profit (Lower): %.2f • "
         "Secure Profit (Upper): %.2f\n",
         this->exit_prices.min_profit, this->exit_prices.max_loss,
         this->exit_prices.lower_secure_profit,
         this->exit_prices.upper_secure_profit);

  printf("Quantity: %.5f\n", open_order_ptr_->quantity);

  const int duration = order_duration(open_order_ptr_);

  printf("Duration: %s\n",
         ::utils::integer_::seconds_to_clock(duration).c_str());

  std::cout << fmt.reset << std::endl;
}

#endif
