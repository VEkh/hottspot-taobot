// TODO: Decide
#ifndef OANDA__TAO_BOT_should_reverse_loss
#define OANDA__TAO_BOT_should_reverse_loss

#include "is_reversal_after.cpp"      // is_reversal_after
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal_after.cpp"  // latest_reversal_after
#include "tao_bot.h"                  // Oanda::TaoBot, reversal_t

// TODO: Decide
#include "day_range_percentile.cpp" // day_range_percentile

bool Oanda::TaoBot::should_reverse_loss() {
  if (!this->api_client.config.max_slow_reverse_loss_count) {
    return false;
  }

  if (!this->open_order_ptr->entry_reversal.is_reversible) {
    return false;
  }

  reversal_t stop_loss_reversal;
  reversals_t stop_reversals = this->secondary_reversals;

  if (this->open_order_ptr->entry_reversal.is_record_only_reversible) {
    const double execution_mid = this->open_order_ptr->execution_price;
    const double max_profit = this->open_order_ptr->max_profit;
    const double ref_epoch = this->open_order_ptr->max_profit_at;
    const order_action_t action = this->open_order_ptr->action;

    const double max_profit_percentile = day_range_percentile(
        this->open_order_ptr->day_candle, this->open_order_ptr, max_profit);

    stop_loss_reversal.at = this->open_order_ptr->max_profit_at;
    stop_loss_reversal.mid = action == order_action_t::BUY
                                 ? execution_mid + max_profit
                                 : execution_mid - max_profit;

    stop_loss_reversal.type =
        this->open_order_ptr->entry_reversal.opposite_type();

    if (max_profit_percentile <
        this->api_client.config.stop_profit_target_percentile) {
      stop_loss_reversal = reversal_t();
    }

    const reversal_t latest_reversal = latest_reversal_after(
        stop_reversals, this->open_order_ptr->timestamp,
        this->open_order_ptr->entry_reversal.opposite_type());

    if (!latest_reversal.at) {
      stop_loss_reversal = reversal_t();
    }

    // stop_loss_reversal = latest_record_reversal(
    //     this->open_order_ptr->entry_reversal.opposite_type());

    // if (!is_reversal_after(stop_loss_reversal, ref_epoch)) {
    //   stop_loss_reversal = reversal_t();
    // }
  } else {
    const double ref_epoch =
        this->api_client.config.should_enter_at_spike
            ? this->open_order_ptr->timestamp -
                  (stop_reversals.timeframe_minutes * 0.5 * 60)
            : this->open_order_ptr->timestamp;

    stop_loss_reversal = latest_reversal_after(
        stop_reversals, ref_epoch,
        this->open_order_ptr->entry_reversal.opposite_type());
  }

  if (!stop_loss_reversal.at) {
    return false;
  }

  if (this->open_order_ptr->profit > 0) {
    return false;
  }

  // TODO: Decide
  stop_loss_reversal.is_reversible = true;
  this->close_order_ptr->stop_profit_reversal = stop_loss_reversal;
  this->slow_reverse_loss_count++;

  return true;
}
#endif
