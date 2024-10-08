// TODO: Decide
#ifndef OANDA__TAO_BOT_ready_to_stop_loss
#define OANDA__TAO_BOT_ready_to_stop_loss

#include "latest_reversal_after.cpp" // latest_reversal_after
#include "tao_bot.h" // Oanda::TaoBot,  reversal_t, reversal_type_t, reversals_t
#include <string>    // std::string

#include "stop_loss_reversals_name.cpp" // stop_loss_reversals_name // TODO: Decide

bool Oanda::TaoBot::ready_to_stop_loss() {
  if (!this->open_order_ptr) {
    return false;
  }

  if (this->api_client.config.should_immediately_stop_loss) {
    return true;
  }

  const reversal_t entry_reversal_ = this->open_order_ptr->entry_reversal;
  const std::string stop_loss_reversals_name_ = stop_loss_reversals_name();

  reversals_t stop_loss_reversals = this->reversals;

  if (stop_loss_reversals_name_ == "secondary") {
    stop_loss_reversals = this->secondary_reversals;
  }

  if (stop_loss_reversals_name_ == "tertiary") {
    stop_loss_reversals = this->tertiary_reversals;
  }

  const reversal_t latest_reversal_ = latest_reversal_after(
      stop_loss_reversals, this->open_order_ptr->timestamp,
      entry_reversal_.type);

  if (!latest_reversal_.at) {
    return false;
  }

  const bool is_latest_reversal_at_loss =
      entry_reversal_.type == reversal_type_t::REVERSAL_LOW
          ? latest_reversal_.mid < entry_reversal_.mid
          : latest_reversal_.mid > entry_reversal_.mid;

  return is_latest_reversal_at_loss;
}

#endif
