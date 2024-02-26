// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "earliest_record_reversal.cpp" // earliest_record_reversal // TODO: Decide
#include "has_reversal_been_used.cpp" // has_reversal_been_used
#include "is_reversing_loss.cpp"      // is_reversing_loss
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal.cpp"        // latest_reversal
#include "tao_bot.h"                  // Alpaca::TaoBot, range_t, reversal_t

bool Alpaca::TaoBot::is_entry_signal_present() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return false;
  }

  if (this->api_client.config.should_reverse_losses && is_reversing_loss()) {
    return true;
  }

  if (this->api_client.config.should_await_reversal_indicator) {
    if (this->reversals.highs.empty() || this->reversals.lows.empty()) {
      return false;
    }

    reversal_t entry_reversal_;

    // TODO: Decide
    // if (this->api_client.config.should_ride_trans_reversals) {
    if (this->api_client.config.should_ride_trans_reversals &&
        this->is_trending) {
      entry_reversal_ = earliest_record_reversal(this->reversals);
    } else {
      entry_reversal_ = latest_record_reversal(this->reversals);
    }

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

    // TODO: Decide
    // if (this->is_trending) {
    //   const std::string key =
    //       entry_reversal_.type == reversal_type_t::REVERSAL_HIGH ? "low"
    //                                                              : "high";

    //   entry_reversal_ = latest_reversal(this->reversals, key);
    // }

    this->entry_reversal = entry_reversal_;

    return true;
  }

  return false;
}

#endif
