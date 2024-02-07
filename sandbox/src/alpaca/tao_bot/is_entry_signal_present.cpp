// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "is_consolidating.cpp"  // is_consolidating
#include "is_reversing_loss.cpp" // is_reversing_loss
#include "nearest_reversal.cpp"  // nearest_reversal
#include "tao_bot.h"             // Alpaca::TaoBot, range_t, reversal_t

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

    const reversal_t nearest_reversal_ = nearest_reversal();

    if (!this->closed_positions.empty()) {
      const position_t last_position = this->closed_positions.back();

      if (last_position.open_order.reversal.type == nearest_reversal_.type &&
          last_position.open_order.reversal.at == nearest_reversal_.at) {
        return false;
      }
    }

    return nearest_reversal_.is_record;
  }

  return false;
}

#endif
