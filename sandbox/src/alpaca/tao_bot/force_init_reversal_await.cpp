#ifndef ALPACA__TAO_BOT_force_init_reversal_await
#define ALPACA__TAO_BOT_force_init_reversal_await

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::force_init_reversal_await() {
  // TODO: Decide
  if (this->api_client.config.should_enter_at_spike) {
    return;
  }

  this->current_trend.at = this->market_availability.market_epochs.open;
  this->current_trend.trend = trend_t::TREND_UP;
}

#endif
