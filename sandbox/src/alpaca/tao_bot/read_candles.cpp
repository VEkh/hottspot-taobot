#ifndef ALPACA__TAO_BOT_read_candles
#define ALPACA__TAO_BOT_read_candles

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::read_candles() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  this->latest_candles = this->db_candle.get_latest({
      .debug = this->api_client.config.debug_sql,
      .end_at_epoch = this->current_epoch,
      .start_at_epoch = this->market_open_epoch,
  });
}

#endif
