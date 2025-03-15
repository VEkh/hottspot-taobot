#ifndef OANDA__TAO_BOT_should_close_position
#define OANDA__TAO_BOT_should_close_position

#include "build_exit_prices.cpp"        // build_exit_prices
#include "is_end_of_quotes.cpp"         // is_end_of_quotes
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "should_reverse_loss.cpp"      // should_reverse_loss
#include "should_reverse_profit.cpp"    // should_reverse_profit // TODO: Decide
#include "should_stop_profit.cpp"       // should_stop_profit
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

  if (is_end_of_quotes()) {
    return true;
  }

  if (max_account_loss_reached()) {
    return true;
  }

  if (this->backtest.is_active &&
      this->backtest.has_reached_end(this->current_epoch)) {
    return true;
  }

  this->exit_prices = build_exit_prices();

  if (this->current_quote.spread() > spread_limit()) {
    return false;
  }

  if (this->exit_prices.stop_loss &&
      this->open_order_ptr->profit <= this->exit_prices.stop_loss) {
    return true;
  }

  if (should_stop_profit()) {
    return true;
  }

  // TODO: Decide
  if (should_reverse_profit()) {
    return true;
  }

  if (should_reverse_loss()) {
    return true;
  }

  return false;
}

#endif
