#ifndef ALPACA__TAO_BOT_reset_backtest
#define ALPACA__TAO_BOT_reset_backtest

#include "advance_current_epoch.cpp"   // advance_current_epoch
#include "build_performance.cpp"       // build_performance
#include "tao_bot.h"                   // Alpaca::TaoBot
#include "update_account_snapshot.cpp" // update_account_snapshot

void Alpaca::TaoBot::reset_backtest() {
  advance_current_epoch(
      this->backtest.next_day_market_open_epoch(this->current_epoch));

  this->closed_positions = {};
  this->performance = build_performance();
  this->started_at = this->current_epoch;
  update_account_snapshot(true);
}

#endif
