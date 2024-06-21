#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

#include "alpaca/utils.cpp"             // Alpaca::Utils
#include "build_exit_prices.cpp"        // build_exit_prices
#include "current_mid.cpp"              // current_mid
#include "is_trending.cpp"              // is_trending
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "tao_bot.h"                    // Alpaca::TaoBot, order_status_t

// TODO: Decide
#include "first_reversal_after.cpp"   // first_reversal_after
#include "is_in_win_percentile.cpp"   // is_in_win_percentile
#include "is_trend_slipping.cpp"      // is_trend_slipping
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal_after.cpp"  // latest_reversal_after

bool Alpaca::TaoBot::should_close_position() {
  if (this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return false;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_INIT) {
    return false;
  }

  if (Alpaca::Utils::is_end_of_trading_period(this->current_epoch)) {
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

  if (this->exit_prices.stop_loss &&
      this->open_order_ptr->profit <= this->exit_prices.stop_loss) {
    return true;
  }

  if (this->exit_prices.stop_profit > 0 &&
      this->open_order_ptr->profit <= this->exit_prices.stop_profit) {
    // TODO: Decide
    // if (this->win_percentile &&
    //     !is_in_win_percentile(this->open_order_ptr,
    //                           this->exit_prices.stop_profit)) {
    //   return false;
    // }

    return true;
  }

  // TODO: Decide
  if (!this->api_client.config.reverse_profit_during.empty()) {
    const std::string config = this->api_client.config.reverse_profit_during;

    reversal_t stop_profit_reversal = latest_reversal_after(
        this->secondary_reversals, this->open_order_ptr->timestamp,
        this->open_order_ptr->entry_reversal.opposite_type());

    if (stop_profit_reversal.at) {
      bool should_close = false;

      if (config == "ALWAYS") {
        should_close = true;
      }

      if (config == "EXCEPT_INIT_REVERSAL" && !this->closed_positions.empty()) {
        should_close = true;
      }

      if (config == "RECORD_AFTER_INIT_AND_SLIP" &&
          !this->closed_positions.empty()) {
        const reversal_t record_reversal =
            latest_record_reversal(this->reversals, stop_profit_reversal.type);

        stop_profit_reversal = first_reversal_after(
            this->secondary_reversals, this->open_order_ptr->timestamp,
            stop_profit_reversal.type, true);

        if (record_reversal.mid == stop_profit_reversal.mid &&
            is_trend_slipping(this->open_order_ptr)) {
          should_close = true;
        }
      }

      if (config == "TRENDING" && is_trending()) {
        should_close = true;
      }

      if (should_close) {
        this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;

        return true;
      }
    }
  }

  return false;
}

#endif
