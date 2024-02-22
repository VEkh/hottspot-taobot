#ifndef ALPACA__TAO_BOT_reset_backtest
#define ALPACA__TAO_BOT_reset_backtest

#include "advance_current_epoch.cpp"   // advance_current_epoch
#include "set_market_open_epoch.cpp"   // set_market_open_epoch
#include "tao_bot.h"                   // Alpaca::TaoBot, candle_t, reversals_t
#include "update_account_snapshot.cpp" // update_account_snapshot

void Alpaca::TaoBot::reset_backtest() {
  update_account_snapshot(true);

  advance_current_epoch(this->backtest.next_day_market_open_epoch(
      this->current_epoch, this->api_client.config.late_start_seconds));

  // `slow_query_countdown` may cause skipping of first daily quote. This
  // will falsely reset the next day's equity to the initial equity.
  update_account_snapshot(true);

  this->bulk_candle = candle_t(); // TODO: Decide
  this->closed_positions = {};
  this->reversals.lows = {};            // TODO: Decide
  this->reversals.highs = {};           // TODO: Decide
  this->secondary_reversals.lows = {};  // TODO: Decide
  this->secondary_reversals.highs = {}; // TODO: Decide
  this->is_trending = false;            // TODO: Decide
  this->performance = performance_t();
  this->started_at = this->current_epoch;

  set_market_open_epoch();
}

#endif
