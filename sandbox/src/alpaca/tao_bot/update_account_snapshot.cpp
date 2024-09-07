#ifndef ALPACA__TAO_BOT_update_account_snapshot
#define ALPACA__TAO_BOT_update_account_snapshot

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot

void Alpaca::TaoBot::update_account_snapshot(const bool force = false) {
  this->backtest.upsert_account_stat({
      .current_epoch = this->current_epoch,
      .current_snapshot = this->account_snapshot,
      .debug = this->api_client.config.debug_sql,
      .end_at = this->market_availability.market_close_epoch,
      .force = force,
  });

  if (!force && !this->backtest.should_exec_slow_query(this->current_epoch)) {
    return;
  }

  this->account_snapshot = this->db_account_stat.get_snapshot({
      .api_key_id = this->api_client.config.api_key_id,
      .debug = this->api_client.config.debug_sql,
      .end_at = this->backtest.is_active ? this->current_epoch : 0,
      .start_at =
          ::utils::time_::beginning_of_day_to_epoch(this->current_epoch),
  });
}

#endif
