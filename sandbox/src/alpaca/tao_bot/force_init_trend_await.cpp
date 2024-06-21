// TODO: Decide
#ifndef ALPACA__TAO_BOT_force_init_trend_await
#define ALPACA__TAO_BOT_force_init_trend_await

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::force_init_trend_await() {
  if (!this->api_client.config.should_await_init_trend) {
    return;
  }

  this->current_trend.at = this->current_epoch;
  this->current_trend.is_initialized = true;
  this->current_trend.trend = trend_t::TREND_UP;
}

#endif
