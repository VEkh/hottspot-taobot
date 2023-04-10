#ifndef ALPACA__TAO_BOT_upsert_backtest_account_stat
#define ALPACA__TAO_BOT_upsert_backtest_account_stat

#include "lib/utils/time.cpp"                  // ::utils::time_
#include "should_backtest_exec_slow_query.cpp" // should_backtest_exec_slow_query
#include "tao_bot.h" // Alpaca::TaoBot, account_snapshot_t

void Alpaca::TaoBot::upsert_backtest_account_stat() {
  if (!this->api_client.config.is_backtest) {
    return;
  }

  if (!should_backtest_exec_slow_query()) {
    return;
  }

  const account_snapshot_t current_snapshot =
      this->db_account_stat.get_snapshot_with_computed_equity({
          .api_key_id = this->api_client.config.api_key_id,
          .starting_from = ::utils::time_::beginning_of_day_to_epoch(
              this->api_client.config.current_epoch),
      });

  bool is_new_day =
      ::utils::time_::beginning_of_day_to_epoch(
          this->api_client.config.current_epoch) >
      ::utils::time_::beginning_of_day_to_epoch(current_snapshot.timestamp);

  const double current_equity = current_snapshot.equity;
  const double original_margin_buying_power =
      current_snapshot.original_margin_buying_power;

  const double equity =
      current_equity ? current_equity
                     : this->api_client.backtest_config.account_starting_equity;

  double margin_buying_power;

  if (!original_margin_buying_power || is_new_day) {
    margin_buying_power =
        equity * this->api_client.backtest_config.account_margin_multiplier;
  } else {
    margin_buying_power = original_margin_buying_power;
  }

  this->db_account_stat.upsert({
      .api_key_id = this->api_client.config.api_key_id,
      .equity = equity,
      .inserted_at = this->api_client.config.current_epoch,
      .margin_buying_power = margin_buying_power,
      .margin_multiplier =
          this->api_client.backtest_config.account_margin_multiplier,
  });
}

#endif
