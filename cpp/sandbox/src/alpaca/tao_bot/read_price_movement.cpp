#ifndef ALPACA__TAO_BOT_read_price_movement
#define ALPACA__TAO_BOT_read_price_movement

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::read_price_movement() {
  this->one_sec_variance_avgs =
      this->quoter.db_quote.get_one_sec_variance_avgs({
          .symbol = this->symbol,
          .timestamp_upper_bound = this->api_client.config.current_time,
      });
}

#endif
