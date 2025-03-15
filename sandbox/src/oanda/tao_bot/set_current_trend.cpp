#ifndef OANDA__TAO_BOT_set_current_trend
#define OANDA__TAO_BOT_set_current_trend

#include "can_open_position.cpp"       // can_open_position
#include "is_entry_signal_present.cpp" // is_entry_signal_present
#include "is_spiking.cpp"              // is_spiking
#include "tao_bot.h"                   // Oanda::TaoBot

void Oanda::TaoBot::set_current_trend() {
  // TODO: Decide
  if (!this->api_client.config.should_enter_at_spike) {
    return;
  }

  if (this->open_order_ptr) {
    return;
  }

  if (this->current_trend.is_initialized) {
    if (is_entry_signal_present() && !can_open_position()) {
      this->current_trend.is_initialized = false;
    }

    return;
  }

  this->current_trend.at = this->current_epoch;
  this->current_trend.trend = trend_t::TREND_CONSOLIDATION;

  if (is_spiking()) {
    this->current_trend.at = this->spike_candles.current.opened_at;
    this->current_trend.is_initialized = true;
    this->current_trend.trend = this->spike_candles.current.trend();
  }
}

#endif
