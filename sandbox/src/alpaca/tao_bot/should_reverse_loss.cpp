// TODO: Decide
#ifndef ALPACA__TAO_BOT_should_reverse_loss
#define ALPACA__TAO_BOT_should_reverse_loss

#include "is_reversal_after.cpp"      // is_reversal_after
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal_after.cpp"  // latest_reversal_after
#include "tao_bot.h"                  // Alpaca::TaoBot, reversal_t

bool Alpaca::TaoBot::should_reverse_loss() {
  // TODO: Decide
  if (!this->api_client.config.should_enter_at_spike) {
    return false;
  }

  if (!this->open_order_ptr->entry_reversal.is_reversible) {
    return false;
  }

  const double ref_epoch = this->open_order_ptr->timestamp;

  reversal_t stop_loss_reversal;
  reversals_t stop_reversals = this->reversals;

  if (this->open_order_ptr->entry_reversal.is_record_only_reversible) {
    stop_loss_reversal = latest_record_reversal(
        this->open_order_ptr->entry_reversal.opposite_type());

    if (!is_reversal_after(stop_loss_reversal, ref_epoch)) {
      stop_loss_reversal = reversal_t();
    }
  } else {
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

  stop_loss_reversal.is_reversible = true;
  this->close_order_ptr->stop_profit_reversal = stop_loss_reversal;

  return true;
}
#endif
