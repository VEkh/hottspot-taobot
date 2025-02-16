#ifndef OANDA__TAO_BOT_should_reverse_loss
#define OANDA__TAO_BOT_should_reverse_loss

#include "is_reversal_after.cpp"      // is_reversal_after
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal_after.cpp"  // latest_reversal_after
#include "tao_bot.h"                  // Oanda::TaoBot, reversal_t

bool Oanda::TaoBot::should_reverse_loss() {
  if (!this->open_order_ptr->entry_reversal.is_reversible) {
    return false;
  }

  reversal_t stop_loss_reversal;
  reversals_t stop_reversals = this->reversals;

  if (this->open_order_ptr->entry_reversal.is_record_only_reversible) {
    stop_loss_reversal = latest_record_reversal(
        this->open_order_ptr->entry_reversal.opposite_type());

    if (!is_reversal_after(stop_loss_reversal,
                           this->open_order_ptr->timestamp)) {
      stop_loss_reversal = reversal_t();
    }
  } else {
    // TODO: Decide
    // const double ref_epoch = this->open_order_ptr->timestamp -
    //                          (stop_reversals.timeframe_minutes * 0.5 * 60);

    const double ref_epoch_shift =
        this->api_client.config.reverse_loss_ref_epoch == "OPEN"
            ? 0.0
            : stop_reversals.timeframe_minutes * 0.5 * 60;

    const double ref_epoch = this->open_order_ptr->timestamp - ref_epoch_shift;

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
