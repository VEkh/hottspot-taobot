#ifndef ALPACA__TAO_BOT_read_candles
#define ALPACA__TAO_BOT_read_candles

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::read_candles() {
  this->latest_candles = this->db_candle.get_latest({
      .debug = this->api_client.config.debug_sql,
      .end_at = this->current_epoch,
      .start_at = this->market_open_epoch,
  });
}

#endif
