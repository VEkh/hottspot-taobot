#ifndef OANDA__TAO_BOT_reset_position
#define OANDA__TAO_BOT_reset_position

/*
 * Oanda::TaoBot
 * order_status_t
 * position_t
 */
#include "tao_bot.h"

#include "build_performance.cpp" // build_performance
#include "reset_orders.cpp"      // reset_orders
#include "write_performance.cpp" // write_performance

void Oanda::TaoBot::reset_position() {
  if (!(this->close_order_ptr && this->open_order_ptr)) {
    return;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_FILLED ||
      this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  const position_t position = {
      .close_order = this->close_order,
      .open_order = this->open_order,
  };

  this->closed_positions.push_back(position);

  reset_orders();

  this->exit_prices = exit_prices_t();
  this->performance = build_performance();
  write_performance();
}

#endif
