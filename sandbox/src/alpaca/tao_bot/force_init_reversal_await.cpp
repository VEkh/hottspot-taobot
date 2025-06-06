#ifndef ALPACA__TAO_BOT_force_init_reversal_await
#define ALPACA__TAO_BOT_force_init_reversal_await

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::force_init_reversal_await() {
  this->current_trend.at = this->market_availability.market_epochs.open;

  if (this->api_client.config.should_await_record_break) {
    this->current_trend.at +=
        this->api_client.config.warm_up_period_hours * 60.0 * 60.0;
  }

  this->current_trend.trend = trend_t::TREND_UP;
}

#endif
