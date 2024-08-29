#ifndef ALPACA__TAO_BOT_read_price_action_stats
#define ALPACA__TAO_BOT_read_price_action_stats

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::read_price_action_stats() {
  this->price_action_stats =
      this->db_price_action.get_stats(this->market_open_epoch);
}

#endif
