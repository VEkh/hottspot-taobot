#ifndef OANDA__TAO_BOT_read_price_movement
#define OANDA__TAO_BOT_read_price_movement

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::read_price_movement() {
  this->avg_one_sec_variances = this->db_quote.get_avg_one_sec_variances({
      .end_at = this->current_epoch,
      .symbol = this->symbol,
  });
}

#endif
