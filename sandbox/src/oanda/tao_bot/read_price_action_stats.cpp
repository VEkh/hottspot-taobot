#ifndef OANDA__TAO_BOT_read_price_action_stats
#define OANDA__TAO_BOT_read_price_action_stats

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::read_price_action_stats() {
  this->price_action_stats = this->db_price_action.get_stats(
      this->market_availability.market_open_epoch);
}

#endif
