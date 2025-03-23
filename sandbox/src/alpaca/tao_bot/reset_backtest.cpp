#ifndef ALPACA__TAO_BOT_reset_backtest
#define ALPACA__TAO_BOT_reset_backtest

#include "advance_current_epoch.cpp"     // advance_current_epoch
#include "force_init_reversal_await.cpp" // force_init_reversal_await
#include "tao_bot.h" // Alpaca::TaoBot, candle_t, quote_t, reversals_t, trend_meta_t
#include "update_account_snapshot.cpp" // update_account_snapshot
#include <algorithm>                   // std::min
#include <time.h>                      // time

void Alpaca::TaoBot::reset_backtest() {
  this->backtest.db_market_close.upsert({
      .api_key_id = this->api_client.config.api_key_id,
      .closed_at = this->market_availability.market_epochs.close,
      .symbol = this->symbol,
  });

  const double next_market_open_epoch =
      std::min((double)time(nullptr),
               this->market_availability.next_market_open_epoch(
                   this->market_availability.market_epochs.close));

  this->backtest.await_env_market_close(
      this->market_availability.market_epochs.close, next_market_open_epoch);

  advance_current_epoch(next_market_open_epoch);

  this->market_availability.set_market_epochs(this->current_epoch);

  this->closed_positions = {};
  this->current_trend = trend_meta_t();
  this->day_candle = candle_t();
  this->db_account_stat.clear_snapshot_stats_cache();
  this->db_candle.clear_cache();
  this->has_stopped_profit = false; // TODO: Decide

  this->current_quote = quote_t();
  this->previous_quote = quote_t();
  this->quotes = {};

  this->latest_candles = {};
  this->performance = performance_t();
  this->reversals = reversals_t();
  this->reversals.timeframe_minutes = this->REVERSAL_TIMEFRAME_MINUTES;
  this->started_at = this->current_epoch;

  force_init_reversal_await();
  update_account_snapshot(true);
}

#endif
