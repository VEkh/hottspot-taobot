// TODO: Decide
#ifndef OANDA__TAO_BOT_force_init_reversal_await
#define OANDA__TAO_BOT_force_init_reversal_await

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::force_init_reversal_await() {
  if (this->api_client.config.should_enter_at_spike) {
    return;
  }

  this->current_trend.at =
      this->market_availability.market_epochs.open +
      this->api_client.config.warm_up_period_hours * 60.0 * 60.0;

  this->current_trend.trend = trend_t::TREND_UP;
}

#endif
