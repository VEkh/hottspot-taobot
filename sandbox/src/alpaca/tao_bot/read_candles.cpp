#ifndef ALPACA__TAO_BOT_read_candles
#define ALPACA__TAO_BOT_read_candles

#include "should_read_candles.cpp" // should_read_candles
#include "tao_bot.h"               // Alpaca::TaoBot

void Alpaca::TaoBot::read_candles() {
  if (!should_read_candles()) {
    return;
  }

  if (this->backtest.is_active) {
    if (this->latest_candles.empty()) {
      this->latest_candles = this->db_candle.get_latest({
          .debug = this->api_client.config.debug_sql,
          .end_at = this->market_availability.market_epochs.close,
          .start_at = this->market_availability.market_epochs.open,
      });
    }

    return;
  }

  this->latest_candles = this->db_candle.get_latest({
      .debug = this->api_client.config.debug_sql,
      .end_at = this->current_epoch,
      .start_at = this->market_availability.market_epochs.open,
  });
}

#endif
