// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "has_reversal_been_used.cpp"  // has_reversal_been_used
#include "is_consolidating.cpp"        // is_consolidating
#include "is_reversing_loss.cpp"       // is_reversing_loss
#include "nearest_record_reversal.cpp" // nearest_record_reversal
#include "nearest_reversal.cpp"        // nearest_reversal
#include "tao_bot.h"                   // Alpaca::TaoBot, range_t, reversal_t

bool Alpaca::TaoBot::is_entry_signal_present() {
  if (!this->api_client.config.should_await_reversal_indicator &&
      !this->api_client.config.should_await_consolidation_indicator) {
    return false;
  }

  // TODO: Decide
  if (this->api_client.config.should_reverse_losses && is_reversing_loss()) {
    return true;
  }

  if (this->api_client.config.should_await_reversal_indicator) {
    if (this->reversals.highs.empty() || this->reversals.lows.empty()) {
      return false;
    }

    reversal_t ref_reversal = nearest_record_reversal(this->reversals);

    if (!this->closed_positions.empty()) {
      const position_t last_position = this->closed_positions.back();

      // TODO: Decide
      if (last_position.open_order.deficit_reclaim_reversal.mid) {
        ref_reversal = last_position.open_order.deficit_reclaim_reversal;
      }

      if (has_reversal_been_used(ref_reversal)) {
        return false;
      }
    }

    this->entry_reversal = ref_reversal;

    return true;
  }

  return false;
}

#endif
