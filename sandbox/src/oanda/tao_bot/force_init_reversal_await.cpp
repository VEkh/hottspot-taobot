#ifndef OANDA__TAO_BOT_force_init_reversal_await
#define OANDA__TAO_BOT_force_init_reversal_await

#include "is_spiking.cpp" // is_spiking // TODO: Decide
#include "tao_bot.h"      // Oanda::TaoBot

void Oanda::TaoBot::force_init_reversal_await() {
  // TODO: Decide
  if (this->open_order_ptr) {
    return;
  }

  if (this->current_trend.is_initialized) {
    return;
  }

  // TODO: Decide
  if (!this->api_client.config.should_await_spike) {
    this->current_trend.at = this->current_epoch;
    this->current_trend.is_initialized = true;
    this->current_trend.trend = trend_t::TREND_UP;

    return;
  }

  this->current_trend.at = this->current_epoch;
  this->current_trend.trend = trend_t::TREND_UP;

  if (is_spiking()) {
    this->current_trend.at = this->spike_candles.current.opened_at;
    this->current_trend.is_initialized = true;
  }
}

#endif
