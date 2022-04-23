#ifndef ALPACA__TAO_BOT_should_terminate
#define ALPACA__TAO_BOT_should_terminate

#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "tao_bot.h"                    // Alpaca::TaoBot, order_status_t
#include <iostream>                     // std::cout, std::endl
#include <stdio.h>                      // printf

bool Alpaca::TaoBot::should_terminate() {
  const bool are_positions_closed =
      (!this->close_order_ptr ||
       this->close_order_ptr->status == order_status_t::ORDER_FILLED);

  if (is_end_of_trading_period()) {
    return are_positions_closed;
  }

  if (max_account_loss_reached()) {
    if (are_positions_closed) {
      std::cout << fmt.bold << fmt.red << std::endl;
      printf(
          "🛑 %.1f%% of account balance lost!! Applying emergency brake.\n",
          this->MAX_ACCOUNT_LOSS_RATIO * 100);
      std::cout << fmt.reset;
    }

    return are_positions_closed;
  }

  return false;
}

#endif
