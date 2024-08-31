#ifndef OANDA__TAO_BOT_should_terminate
#define OANDA__TAO_BOT_should_terminate

#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "tao_bot.h"                    // Oanda::TaoBot, order_status_t
#include <iostream>                     // std::cout, std::endl
#include <stdio.h>                      // printf

bool Oanda::TaoBot::should_terminate() {
  const bool are_positions_closed =
      !this->close_order_ptr ||
      this->close_order.status == order_status_t::ORDER_FILLED;

  if (this->market_availability.is_end_of_trading_period(this->current_epoch)) {
    return are_positions_closed;
  }

  if (max_account_loss_reached()) {
    if (are_positions_closed) {
      std::cout << fmt.bold << fmt.red << std::endl;
      puts("🛑 Max account balance lost!! Applying emergency brake.");
      std::cout << fmt.reset;
    }

    return are_positions_closed;
  }

  return false;
}

#endif
