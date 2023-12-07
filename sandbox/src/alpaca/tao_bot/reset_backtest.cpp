#ifndef ALPACA__TAO_BOT_reset_backtest
#define ALPACA__TAO_BOT_reset_backtest

#include "advance_current_epoch.cpp"   // advance_current_epoch
#include "tao_bot.h"                   // Alpaca::TaoBot
#include "update_account_snapshot.cpp" // update_account_snapshot

void Alpaca::TaoBot::reset_backtest() {
  update_account_snapshot(true);

  advance_current_epoch(this->backtest.next_day_market_open_epoch(
      this->current_epoch, this->api_client.config.late_start_seconds));

  if (this->candle_predictor.should_predict()) {
    this->candle_predictor.toggle_inverse_predictions(
        this->api_client.config.ml.candle_predict.inverse_predictions);
  }

  if (this->api_client.config.alt_stop_profit) {
    this->api_client.config.use_alt_stop_profit = false;
  }

  // `slow_query_countdown` may cause skipping of first daily quote. This
  // will falsely reset the next day's equity to the initial equity.
  update_account_snapshot(true);

  this->closed_positions = {};
  this->performance = performance_t();
  this->started_at = this->current_epoch;
}

#endif
