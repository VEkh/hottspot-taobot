#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

#include "alpaca/utils.cpp"             // Alpaca::Utils
#include "build_exit_prices.cpp"        // build_exit_prices
#include "current_mid.cpp"              // current_mid
#include "does_position_exist.cpp"      // does_position_exist
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

  if (Alpaca::Utils::is_end_of_trading_period(
          this->current_epoch,
          this->api_client.config.terminate_after_seconds)) {
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

  if (should_stop_profit()) {
    return true;
  }

  if (this->exit_prices.stop_loss &&
      this->open_order_ptr->profit <= this->exit_prices.stop_loss) {
    return true;
  }

  if (this->candle_predictor.should_predict(does_position_exist()) &&
      !this->candle_predictor.config.hold_winning_prediction) {
    if (this->candle_predictor.config.rollover_positions) {
      return this->candle_predictor.should_close_position({
          .current_epoch = this->current_epoch,
          .open_order_action = this->open_order_ptr->action,
          .open_order_max_profit = this->open_order_ptr->max_profit,
          .open_order_opened_at = this->open_order_ptr->timestamp,
          .open_order_profit = this->open_order_ptr->profit,
          .open_order_stop_profit = this->exit_prices.stop_profit,
      });
    }

    return this->candle_predictor.are_predictions_stale(
        this->open_order_ptr->timestamp);
  }

  if (this->exit_prices.stop_profit &&
      this->open_order_ptr->max_profit >= this->exit_prices.stop_profit &&
      this->open_order_ptr->profit > 0 &&
      this->open_order_ptr->profit <= this->exit_prices.trailing_stop_profit) {
    return true;
  }

  if (this->api_client.config.is_stop_profit_decayed &&
      this->exit_prices.stop_profit &&
      this->exit_prices.stop_profit < this->avg_one_sec_variances.running) {
    return true;
  }

  return false;
}

#endif
