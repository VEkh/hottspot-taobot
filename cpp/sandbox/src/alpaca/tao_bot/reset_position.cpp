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

#include "build_performance.cpp"   // build_performance
#include "set_trade_direction.cpp" // set_trade_direction
#include "write_performance.cpp"   // write_performance
#include <ctime>                   // std::time, std::time_t

void Alpaca::TaoBot::reset_position() {
  if (!(this->close_order_ptr && this->open_order_ptr &&
        this->hedge_close_order_ptr && this->hedge_open_order_ptr)) {
    return;
  }

  if (!(this->close_order_ptr->status == order_status_t::ORDER_FILLED &&
        this->hedge_close_order_ptr->status == order_status_t::ORDER_FILLED)) {
    return;
  }

  const position_t position = {
      .close_order = this->close_order,
      .hedge_close_order = this->hedge_close_order,
      .hedge_open_order = this->hedge_open_order,
      .open_order = this->open_order,
  };

  this->closed_positions.push_back(position);

  this->close_order_ptr = nullptr;
  this->exit_prices = exit_prices_t();
  this->hedge_close_order_ptr = nullptr;
  this->hedge_open_order_ptr = nullptr;
  this->open_order_ptr = nullptr;
  this->signal = signal_t();

  this->performance = build_performance();
  set_trade_direction();
  write_performance();
}

#endif
