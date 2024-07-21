#ifndef ALPACA__TAO_BOT_reset_backtest
#define ALPACA__TAO_BOT_reset_backtest

#include "advance_current_epoch.cpp"     // advance_current_epoch
#include "force_init_reversal_await.cpp" // force_init_reversal_await
#include "lib/utils/time.cpp"            // ::utils::time_
#include "set_market_close_epoch.cpp"    // set_market_close_epoch
#include "set_market_open_epoch.cpp"     // set_market_open_epoch
#include "tao_bot.h" // Alpaca::TaoBot, candle_t, quote_t, reversals_t, trend_meta_t
#include "update_account_snapshot.cpp" // update_account_snapshot

void Alpaca::TaoBot::reset_backtest() {
  update_account_snapshot(true);

  this->backtest.db_market_close.upsert({
      .api_key_id = this->api_client.config.api_key_id,
      .closed_at =
          ::utils::time_::beginning_of_day_to_epoch(this->current_epoch),
      .symbol = this->symbol,
  });

  advance_current_epoch(this->backtest.next_day_market_open_epoch(
      this->current_epoch, this->api_client.config.late_start_seconds));

  // `slow_query_countdown` may cause skipping of first daily quote. This
  // will falsely reset the next day's equity to the initial equity.
  update_account_snapshot(true);

  this->closed_positions = {};
  this->current_trend = trend_meta_t();
  this->day_candle = candle_t();
  this->db_candle.clear_cache();

  this->current_quote = quote_t();
  this->previous_quote = quote_t();
  this->quotes = {};

  this->latest_candles = {};
  this->performance = performance_t();
  this->reversals = reversals_t();
  this->reversals.timeframe_minutes =
      this->api_client.config.reversal_timeframe_minutes;
  this->secondary_reversals = reversals_t();
  this->secondary_reversals.timeframe_minutes =
      this->api_client.config.secondary_reversal_timeframe_minutes;
  this->started_at = this->current_epoch;

  force_init_reversal_await();
  set_market_close_epoch();
  set_market_open_epoch();
}

#endif
