#ifndef OANDA__TAO_BOT_update_account_snapshot
#define OANDA__TAO_BOT_update_account_snapshot

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::update_account_snapshot(
    const update_account_snapshot_args_t args =
        update_account_snapshot_args_t()) {
  this->backtest.upsert_account_stat({
      .current_epoch = this->current_epoch,
      .current_snapshot = this->account_snapshot,
      .debug = this->api_client.config.debug_sql,
      .force = args.force,
      .market_epochs = this->market_availability.market_epochs,
      .reset_equity = args.reset_equity,
  });

  if (!args.force &&
      !this->backtest.should_exec_slow_query(this->current_epoch)) {
    return;
  }

  this->account_snapshot = this->db_account_stat.get_snapshot({
      .api_key_id = this->api_client.config.account_id,
      .debug = this->api_client.config.debug_sql,
      .end_at = this->backtest.is_active ? this->current_epoch : 0,
      .start_at = this->market_availability.market_epochs.open,
      .use_cache = true,
  });
}

#endif
