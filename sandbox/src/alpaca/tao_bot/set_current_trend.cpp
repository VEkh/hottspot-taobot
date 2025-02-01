// TODO: Decide
#ifndef ALPACA__TAO_BOT_set_current_trend
#define ALPACA__TAO_BOT_set_current_trend

#include "can_open_position.cpp"             // can_open_position
#include "is_spike_entry_signal_present.cpp" // is_spike_entry_signal_present
#include "is_spiking.cpp"                    // is_spiking
#include "tao_bot.h"                         // Alpaca::TaoBot

void Alpaca::TaoBot::set_current_trend() {
  if (!this->api_client.config.should_enter_at_spike) {
    return;
  }

  if (this->open_order_ptr) {
    return;
  }

  if (this->current_trend.is_initialized) {
    if (is_spike_entry_signal_present() && !can_open_position()) {
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
