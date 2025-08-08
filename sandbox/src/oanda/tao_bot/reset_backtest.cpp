#ifndef OANDA__TAO_BOT_reset_backtest
#define OANDA__TAO_BOT_reset_backtest

#include "advance_current_epoch.cpp"     // advance_current_epoch
#include "force_init_reversal_await.cpp" // force_init_reversal_await
#include "set_current_trend.cpp"         // set_current_trend
#include "tao_bot.h" // Oanda::TaoBot, candle_t, quote_t, reversals_t, spike_candles_t, trend_meta_t
#include "update_account_snapshot.cpp" // update_account_snapshot
#include <algorithm>                   // std::min
#include <time.h>                      // time

void Oanda::TaoBot::reset_backtest() {
  this->backtest.db_market_close.upsert({
      .api_key_id = this->api_client.config.account_id,
      .closed_at = this->market_availability.market_epochs.close,
      .symbol = this->symbol,
  });

  this->backtest.await_env_market_close(
      this->market_availability.market_epochs.close,
      this->market_availability.market_epochs.next);

  advance_current_epoch(this->market_availability.market_epochs.next);

  this->market_availability.set_market_epochs({
      .current_epoch = this->current_epoch,
      .market_duration_hours = this->api_client.config.market_duration_hours,
      .open_central_time = this->api_client.config.market_open_central_time,
  });

  this->closed_positions = {};
  this->current_trend = trend_meta_t();
  this->day_candle = candle_t();
  this->db_account_stat.clear_snapshot_stats_cache();
  this->db_candle.clear_cache();
  this->spike_candles = spike_candles_t();
  this->warm_up_candle = candle_t();

  this->current_quote = quote_t();
  this->previous_quote = quote_t();
  this->quotes = {};

  this->latest_candles = {};
  this->performance = performance_t();
  this->reversals = reversals_t();
  this->reversals.timeframe_minutes = this->REVERSAL_TIMEFRAME_MINUTES;

  this->started_at = this->current_epoch;

  set_current_trend();
  force_init_reversal_await();
  update_account_snapshot(true);
}

#endif
