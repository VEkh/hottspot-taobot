#ifndef OANDA__TAO_BOT_force_init_reversal_await
#define OANDA__TAO_BOT_force_init_reversal_await

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::force_init_reversal_await() {
  this->current_trend.at = this->market_open_epoch;
  this->current_trend.trend = trend_t::TREND_UP;
}

#endif
