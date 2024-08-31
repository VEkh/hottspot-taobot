#ifndef OANDA__TAO_BOT_should_close_position
#define OANDA__TAO_BOT_should_close_position

#include "build_exit_prices.cpp"        // build_exit_prices
#include "current_spread.cpp"           // current_spread
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "spread_limit.cpp"             // spread_limit
#include "tao_bot.h"                    // Oanda::TaoBot, order_status_t

bool Oanda::TaoBot::should_close_position() {
  if (this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return false;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_INIT) {
    return false;
  }

  if (this->market_availability.is_end_of_trading_period(this->current_epoch)) {
    return true;
  }

  if (max_account_loss_reached()) {
    return true;
  }

  this->exit_prices = build_exit_prices();

  if (current_spread() > spread_limit()) {
    return false;
  }

  if (this->open_order_ptr->profit <= this->exit_prices.stop_loss) {
    return true;
  }

  return false;
}

#endif
