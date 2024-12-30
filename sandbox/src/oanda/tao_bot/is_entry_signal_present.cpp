#ifndef OANDA__TAO_BOT_is_entry_signal_present
#define OANDA__TAO_BOT_is_entry_signal_present

#include "tao_bot.h" // Oanda::TaoBot, position_t, reversal_t, reversal_type_t

bool Oanda::TaoBot::is_entry_signal_present() {
  reversal_t entry_reversal_;

  if (!this->closed_positions.empty()) {
    const position_t last_position = this->closed_positions.back();

    if (last_position.close_order.stop_profit_reversal.at) {
      entry_reversal_ = last_position.close_order.stop_profit_reversal;
    }
  }

  const bool is_after_entry_epoch =
      this->current_epoch >=
      this->current_trend.at + this->spike_candles.current.duration_seconds();

  if (this->current_trend.is_initialized && is_after_entry_epoch) {
    entry_reversal_.at = this->spike_candles.previous.opened_at;
    entry_reversal_.is_record_only_reversible = false;
    entry_reversal_.is_reversible = true;

    if (this->spike_candles.previous.trend() == trend_t::TREND_DOWN) {
      entry_reversal_.mid = this->spike_candles.previous.high;
      entry_reversal_.type = reversal_type_t::REVERSAL_HIGH;
    } else if (this->spike_candles.previous.trend() == trend_t::TREND_UP) {
      entry_reversal_.mid = this->spike_candles.previous.low;
      entry_reversal_.type = reversal_type_t::REVERSAL_LOW;
    }
  }

  if (entry_reversal_.at) {
    this->entry_reversal = entry_reversal_;

    return true;
  }

  return false;
}

#endif
