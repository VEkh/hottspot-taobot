#ifndef OANDA__TAO_BOT_read_price_movement
#define OANDA__TAO_BOT_read_price_movement

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::read_price_movement() {
  this->one_sec_variance_avgs = this->db_quote.get_one_sec_variance_avgs({
      .symbol = this->symbol,
      .timestamp_upper_bound = this->current_epoch,
  });
}

#endif
