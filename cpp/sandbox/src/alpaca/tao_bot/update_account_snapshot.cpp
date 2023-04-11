#ifndef ALPACA__TAO_BOT_update_account_snapshot
#define ALPACA__TAO_BOT_update_account_snapshot

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

void Alpaca::TaoBot::update_account_snapshot() {
  this->backtest.upsert_account_stat(this->current_epoch);

  if (!this->backtest.should_exec_slow_query()) {
    return;
  }

  this->account_snapshot = this->db_account_stat.get_snapshot({
      .api_key_id = this->api_client.config.api_key_id,
      .session_started_at = this->started_at,
      .starting_from =
          ::utils::time_::beginning_of_day_to_epoch(this->current_epoch),
  });
}

#endif
