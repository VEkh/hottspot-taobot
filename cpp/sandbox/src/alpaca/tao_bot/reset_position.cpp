#ifndef ALPACA__TAO_BOT_reset_position
#define ALPACA__TAO_BOT_reset_position

/*
 * Alpaca::TaoBot
 * exit_prices_t
 * order_status_t
 * position_t
 * signal_t
 */
#include "tao_bot.h"

#include "build_performance.cpp"     // build_performance
#include "fetch_account_balance.cpp" // fetch_account_balance
#include "write_performance.cpp"     // write_performance

void Alpaca::TaoBot::reset_position() {
  if (!(this->close_order_ptr && this->open_order_ptr)) {
    return;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  const position_t position = {
      .close_order = this->close_order,
      .open_order = this->open_order,
  };

  this->closed_positions.push_back(position);

  this->close_order_ptr = nullptr;
  this->exit_prices = exit_prices_t();
  this->open_order_ptr = nullptr;

  this->account_balance =
      fetch_account_balance(this->api_client, this->account_balance);
  this->performance = build_performance();
  write_performance();
}

#endif
