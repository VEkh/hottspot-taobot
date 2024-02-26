// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_primary_reversal_reversing
#define ALPACA__TAO_BOT_is_primary_reversal_reversing

#include "latest_reversal.cpp" // latest_reversal
#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, reversal_type_t // TODO: Decide

bool Alpaca::TaoBot::is_primary_reversal_reversing() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return false;
  }

  if (!this->open_order_ptr) {
    return false;
  }

  if (!this->secondary_reversals.timeframe_minutes) {
    return false;
  }

  if (this->secondary_reversals.lows.empty() ||
      this->secondary_reversals.highs.empty()) {
    return false;
  }

  if (this->open_order_ptr->entry_reversal.timeframe_minutes !=
      this->reversals.timeframe_minutes) {
    return false;
  }

  if (this->open_order_ptr->profit >= 0.5 * this->open_order_ptr->max_profit) {
    return false;
  }

  const order_action_t open_action = this->open_order_ptr->action;

  const reversal_t secondary_reversal =
      latest_reversal(this->secondary_reversals);

  const bool is_trans_secondary =
      (open_action == order_action_t::BUY &&
       secondary_reversal.type == reversal_type_t::REVERSAL_HIGH) ||
      (open_action == order_action_t::SELL &&
       secondary_reversal.type == reversal_type_t::REVERSAL_LOW);

  if (!is_trans_secondary) {
    return false;
  }

  if (secondary_reversal.at <= this->open_order_ptr->timestamp) {
    return false;
  }

  this->open_order_ptr->deficit_reclaim_reversal = secondary_reversal;

  return true;
}

#endif
