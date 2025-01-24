#ifndef BACKTEST_upsert_account_stat
#define BACKTEST_upsert_account_stat

#include "backtest.h" // Backtest, account_snapshot_t, market_epochs_t

void Backtest::upsert_account_stat(const upsert_account_stat_args_t args) {
  const double current_epoch = args.current_epoch;
  const bool force = args.force;
  const market_epochs_t market_epochs = args.market_epochs;

  if (!this->is_active) {
    return;
  }

  if (!force && !should_exec_slow_query(current_epoch)) {
    return;
  }

  const account_snapshot_t updated_current_snapshot =
      this->db_account_stat.get_snapshot_with_computed_equity({
          .api_key_id = this->config.api_key_id,
          .current_snapshot = args.current_snapshot,
          .debug = args.debug,
          .end_at = market_epochs.close,
          .start_at = market_epochs.open,
      });

  const bool is_new_day = current_epoch == market_epochs.open;
  const double current_equity = updated_current_snapshot.equity;

  const double original_margin_buying_power =
      updated_current_snapshot.original_margin_buying_power;

  const double equity =
      current_equity ? current_equity : this->config.account_starting_equity;

  double margin_buying_power;

  if (!original_margin_buying_power || is_new_day) {
    margin_buying_power = equity * this->config.account_margin_multiplier;
  } else {
    margin_buying_power = original_margin_buying_power;
  }

  this->db_account_stat.upsert({
      .api_key_id = this->config.api_key_id,
      .equity = equity,
      .inserted_at = current_epoch,
      .margin_buying_power = margin_buying_power,
      .margin_multiplier = this->config.account_margin_multiplier,
  });
}

#endif
