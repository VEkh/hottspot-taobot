#ifndef OANDA__TAO_BOT_update_account_snapshot
#define OANDA__TAO_BOT_update_account_snapshot

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::update_account_snapshot() {
  this->account_snapshot = this->db_account_stat.get_snapshot({
      .api_key_id = this->api_client.config.account_id,
      .debug = this->api_client.config.debug_sql,
      .start_at = this->market_availability.market_epochs.open,
  });
}

#endif
