#ifndef ALPACA__TAO_BOT_should_use_price_movement
#define ALPACA__TAO_BOT_should_use_price_movement

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::should_use_price_movement() {
  return !this->api_client.config.should_await_reversal_indicator;
}

#endif
