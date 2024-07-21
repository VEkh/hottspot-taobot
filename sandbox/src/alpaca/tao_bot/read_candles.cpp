#ifndef ALPACA__TAO_BOT_read_candles
#define ALPACA__TAO_BOT_read_candles

#include "should_read_candles.cpp" // should_read_candles
#include "tao_bot.h"               // Alpaca::TaoBot

void Alpaca::TaoBot::read_candles() {
  if (!should_read_candles()) {
    return;
  }

  if (this->backtest.is_active && this->db_candle.cache.empty()) {
    this->db_candle.get_latest({
        .debug = this->api_client.config.debug_sql,
        .end_at = this->market_close_epoch,
        .start_at = this->market_open_epoch,
        .write_cache = true,
    });
  }

  this->latest_candles = this->db_candle.get_latest({
      .debug = this->api_client.config.debug_sql,
      .end_at = this->current_epoch,
      .read_cache = this->backtest.is_active,
      .start_at = this->market_open_epoch,
  });
}

#endif
