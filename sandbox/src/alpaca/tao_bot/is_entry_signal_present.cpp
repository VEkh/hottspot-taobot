// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "has_reversal_been_used.cpp"  // has_reversal_been_used
#include "is_reversing_loss.cpp"       // is_reversing_loss
#include "nearest_record_reversal.cpp" // nearest_record_reversal
#include "nearest_reversal.cpp"        // nearest_reversal
#include "tao_bot.h"                   // Alpaca::TaoBot, range_t, reversal_t

bool Alpaca::TaoBot::is_entry_signal_present() {
  if (!this->api_client.config.should_await_reversal_indicator &&
      !this->api_client.config.should_await_consolidation_indicator) {
    return false;
  }

  if (this->api_client.config.should_reverse_losses && is_reversing_loss()) {
    return true;
  }

  if (this->api_client.config.should_await_reversal_indicator) {
    if (this->reversals.highs.empty() || this->reversals.lows.empty()) {
      return false;
    }

    reversal_t entry_reversal_ = nearest_record_reversal(this->reversals);

    if (!this->closed_positions.empty()) {
      const position_t last_position = this->closed_positions.back();

      if (last_position.open_order.deficit_reclaim_reversal.mid) {
        entry_reversal_ = last_position.open_order.deficit_reclaim_reversal;
      }

      if (has_reversal_been_used(entry_reversal_)) {
        return false;
      }
    }

    this->ref_reversal = entry_reversal_;

    if (this->is_trending) {
      const std::string key =
          entry_reversal_.type == reversal_type_t::REVERSAL_HIGH ? "low"
                                                                 : "high";

      entry_reversal_ = nearest_reversal(this->reversals, key);
    }

    this->entry_reversal = entry_reversal_;

    return true;
  }

  return false;
}

#endif
