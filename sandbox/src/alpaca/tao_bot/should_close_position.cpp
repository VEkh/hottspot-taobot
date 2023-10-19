#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

#include "build_exit_prices.cpp"        // build_exit_prices
#include "current_mid.cpp"              // current_mid
#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "should_stop_profit.cpp"       // should_stop_profit
#include "tao_bot.h"                    // Alpaca::TaoBot, order_status_t

bool Alpaca::TaoBot::should_close_position() {
  if (this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return false;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_INIT) {
    return false;
  }

  if (is_end_of_trading_period()) {
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

  if (!this->exit_prices.max_loss || !this->exit_prices.min_profit) {
    return false;
  }

  if (this->open_order_ptr->profit <= this->exit_prices.max_loss) {
    return true;
  }

  if (should_stop_profit()) {
    return true;
  }

  if (this->five_min_predict.should_predict()) {
    return this->five_min_predict.should_close_position({
        .current_epoch = this->current_epoch,
        .current_mid = current_mid(),
        .open_order_action = this->open_order_ptr->action,
        .open_order_execution = this->open_order_ptr->execution_price,
        .open_order_max_profit = this->open_order_ptr->max_profit,
        .open_order_profit = this->open_order_ptr->profit,
        .range_buffer = this->avg_one_sec_variances.running * 60,
    });
  } else {
    if (this->open_order_ptr->max_profit >= this->exit_prices.min_profit &&
        this->open_order_ptr->profit <=
            this->exit_prices.trailing_stop_profit) {
      return true;
    }
  }

  return false;
}

#endif
