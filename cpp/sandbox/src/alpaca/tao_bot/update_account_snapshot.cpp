#ifndef ALPACA__TAO_BOT_update_account_snapshot
#define ALPACA__TAO_BOT_update_account_snapshot

#include "lib/utils/time.cpp"                  // ::utils::time_
#include "should_backtest_exec_slow_query.cpp" // should_backtest_exec_slow_query
#include "tao_bot.h"                           // Alpaca::TaoBot
#include "upsert_backtest_account_stat.cpp"    // upsert_backtest_account_stat

void Alpaca::TaoBot::update_account_snapshot() {
  if (!should_backtest_exec_slow_query()) {
    return;
  }

  upsert_backtest_account_stat();

  this->account_snapshot = this->db_account_stat.get_snapshot({
      .api_key_id = this->api_client.config.api_key_id,
      .session_started_at = this->started_at,
      .starting_from = ::utils::time_::beginning_of_day_to_epoch(
          this->api_client.config.current_epoch),
  });
}

#endif
