// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

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

    const reversal_t ref_reversal =
        nearest_record_reversal(this->current_epoch).second;

    if (!this->closed_positions.empty()) {
      const position_t last_position = this->closed_positions.back();

      if (last_position.open_order.reversal.type == ref_reversal.type &&
          last_position.open_order.reversal.at == ref_reversal.at) {
        return false;
      }
    }

    this->entry_reversal = ref_reversal;

    const double static_one_sec_variance = this->avg_one_sec_variances.running;
    const double stop_loss_ratio = this->api_client.config.stop_loss_ratio;
    const double stop_loss = stop_loss_ratio * static_one_sec_variance;

    const double mid = current_mid();
    const double reversal_price = ref_reversal.mid;

    const double reversal_delta = abs(mid - reversal_price);

    if (reversal_delta > abs(stop_loss)) {
      return false;
    };

    return true;
  }

  return false;
}

#endif
