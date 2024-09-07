#ifndef ALPACA__TAO_BOT_reset_backtest
#define ALPACA__TAO_BOT_reset_backtest

#include "advance_current_epoch.cpp"     // advance_current_epoch
#include "force_init_reversal_await.cpp" // force_init_reversal_await
#include "lib/utils/time.cpp"            // ::utils::time_
#include "read_price_action_stats.cpp"   // read_price_action_stats
#include "tao_bot.h" // Alpaca::TaoBot, candle_t, quote_t, reversals_t, trend_meta_t
#include "update_account_snapshot.cpp" // update_account_snapshot

void Alpaca::TaoBot::reset_backtest() {
  this->backtest.db_market_close.upsert({
      .api_key_id = this->api_client.config.api_key_id,
      .closed_at =
          ::utils::time_::beginning_of_day_to_epoch(this->current_epoch),
      .symbol = this->symbol,
  });

  const double next_market_open_epoch =
      this->backtest.next_market_open_epoch(this->current_epoch);

  this->backtest.await_env_market_close(this->current_epoch,
                                        next_market_open_epoch);

  update_account_snapshot(true);
  advance_current_epoch(next_market_open_epoch);

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
  this->started_at = this->current_epoch;

  this->market_availability.set_market_close_epoch(this->current_epoch);
  this->market_availability.set_market_open_epoch(this->current_epoch);

  force_init_reversal_await();
  read_price_action_stats();
}

#endif
