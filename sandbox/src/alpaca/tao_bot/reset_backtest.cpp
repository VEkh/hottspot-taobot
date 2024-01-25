#ifndef ALPACA__TAO_BOT_reset_backtest
#define ALPACA__TAO_BOT_reset_backtest

#include "advance_current_epoch.cpp"   // advance_current_epoch
#include "set_market_open_epoch.cpp"   // set_market_open_epoch
#include "tao_bot.h"                   // Alpaca::TaoBot
#include "update_account_snapshot.cpp" // update_account_snapshot

void Alpaca::TaoBot::reset_backtest() {
  update_account_snapshot(true);

  advance_current_epoch(this->backtest.next_day_market_open_epoch(
      this->current_epoch, this->api_client.config.late_start_seconds));

  // `slow_query_countdown` may cause skipping of first daily quote. This
  // will falsely reset the next day's equity to the initial equity.
  update_account_snapshot(true);

  // TODO: Decide
  if (this->api_client.config.should_toggle_profit_timeout_seconds) {
    this->api_client.config.should_use_alt_profit_timeout_seconds = false;
  }

  if (this->api_client.config.should_toggle_stop_loss) {
    this->api_client.config.should_use_alt_stop_loss = false;
  }

  // TODO: Decide
  if (this->api_client.config.should_toggle_stop_profit) {
    this->api_client.config.should_use_alt_stop_profit = false;
  }

  // TODO: Decide
  if (this->api_client.config.should_toggle_stop_profit_decay) {
    this->api_client.config.is_stop_profit_decayed = false;
  }

  this->closed_positions = {};
  this->performance = performance_t();
  this->reversals = reversals_t(); // TODO: Decide
  this->started_at = this->current_epoch;

  set_market_open_epoch();
}

#endif
