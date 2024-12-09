#ifndef OANDA__TAO_BOT_should_terminate
#define OANDA__TAO_BOT_should_terminate

#include "is_end_of_quotes.cpp"         // is_end_of_quotes
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "tao_bot.h"                    // Oanda::TaoBot, order_status_t
#include <iostream>                     // std::cout, std::endl
#include <stdio.h>                      // printf

bool Oanda::TaoBot::should_terminate() {
  const bool are_positions_closed =
      !this->close_order_ptr ||
      this->close_order.status == order_status_t::ORDER_FILLED;

  if (!this->market_availability.is_market_day(this->current_epoch)) {
    return are_positions_closed;
  }

  if (this->market_availability.is_end_of_trading_period(this->current_epoch)) {
    return are_positions_closed;
  }

  if (is_end_of_quotes()) {
    return are_positions_closed;
  }

  if (this->backtest.is_active &&
      this->backtest.has_reached_end(this->current_epoch)) {
    if (are_positions_closed) {
      std::cout << fmt.bold << fmt.red << std::endl;
      puts("⌛ Reached end of backtest time range.");
      std::cout << fmt.reset;
    }

    return are_positions_closed;
  }

  // TODO: FIX: If this happens on Friday in backtest, it skips the next week
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
