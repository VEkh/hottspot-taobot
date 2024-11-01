// TODO: Decide
#ifndef OANDA__TAO_BOT_should_reverse_loss
#define OANDA__TAO_BOT_should_reverse_loss

#include "is_reversal_after.cpp"      // is_reversal_after
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal_after.cpp"  // latest_reversal_after
#include "tao_bot.h"                  // Oanda::TaoBot, reversal_t

bool Oanda::TaoBot::should_reverse_loss() {
  if (!this->api_client.config.should_reverse_loss) {
    return false;
  }

  if (!this->open_order_ptr->entry_reversal.is_reversible) {
    return false;
  }

  const double ref_epoch = this->open_order_ptr->timestamp;

  reversal_t stop_profit_reversal;

  if (this->open_order_ptr->entry_reversal.is_record_only_reversible) {
    stop_profit_reversal = latest_record_reversal(
        this->open_order_ptr->entry_reversal.opposite_type());

    if (!is_reversal_after(stop_profit_reversal, ref_epoch)) {
      stop_profit_reversal = reversal_t();
    }
  } else {
    stop_profit_reversal = latest_reversal_after(
        this->secondary_reversals, ref_epoch,
        this->open_order_ptr->entry_reversal.opposite_type());
  }

  if (!stop_profit_reversal.at) {
    return false;
  }

  if (this->open_order_ptr->profit > 0) {
    return false;
  }

  this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;

  return true;
}
#endif
