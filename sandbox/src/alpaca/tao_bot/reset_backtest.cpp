#ifndef ALPACA__TAO_BOT_reset_backtest
#define ALPACA__TAO_BOT_reset_backtest

#include "advance_current_epoch.cpp"  // advance_current_epoch
#include "force_init_trend_await.cpp" // force_init_trend_await // TODO: Decide
#include "set_market_open_epoch.cpp"  // set_market_open_epoch
#include "tao_bot.h" // Alpaca::TaoBot, candle_t, reversals_t, trend_meta_t
#include "update_account_snapshot.cpp" // update_account_snapshot

void Alpaca::TaoBot::reset_backtest() {
  update_account_snapshot(true);

  advance_current_epoch(this->backtest.next_day_market_open_epoch(
      this->current_epoch, this->api_client.config.late_start_seconds));

  // `slow_query_countdown` may cause skipping of first daily quote. This
  // will falsely reset the next day's equity to the initial equity.
  update_account_snapshot(true);

  this->closed_positions = {};
  this->current_trend = trend_meta_t();
  this->day_candle = candle_t();
  this->performance = performance_t();
  this->reversals = reversals_t();
  this->reversals.timeframe_minutes =
      this->api_client.config.reversal_timeframe_minutes;
  this->secondary_reversals = reversals_t();
  this->secondary_reversals.timeframe_minutes =
      this->api_client.config.secondary_reversal_timeframe_minutes;
  this->started_at = this->current_epoch;
  // TODO: Decide
  this->tertiary_reversals = reversals_t();
  this->tertiary_reversals.timeframe_minutes =
      this->api_client.config.tertiary_reversal_timeframe_minutes;

  force_init_trend_await();
  set_market_open_epoch();
}

#endif
