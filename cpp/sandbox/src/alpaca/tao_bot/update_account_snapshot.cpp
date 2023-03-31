#ifndef ALPACA__TAO_BOT_update_account_snapshot
#define ALPACA__TAO_BOT_update_account_snapshot

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot
#include <algorithm>          // std::min

void Alpaca::TaoBot::update_account_snapshot() {
  this->account_snapshot = this->db_account_stat.get_snapshot({
      .api_key_id = this->api_client.config.api_key_id,
      .session_started_at = this->started_at,
      .starting_from = std::min(::utils::time_::beginning_of_day_to_epoch(),
                                this->started_at),
  });
}

#endif
