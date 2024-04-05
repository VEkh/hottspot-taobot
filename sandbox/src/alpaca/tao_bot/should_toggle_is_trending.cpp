#ifndef ALPACA__TAO_BOT_should_toggle_is_trending
#define ALPACA__TAO_BOT_should_toggle_is_trending

#include "is_trending.cpp" // is_trending
#include "tao_bot.h"       // Alpaca::TaoBot, position_t

bool Alpaca::TaoBot::should_toggle_is_trending(const order_t &order) {
  if (!this->open_order_ptr) {
    return false;
  }

  if (!this->api_client.config.should_await_reversal_indicator) {
    return false;
  }

  if (is_trending()) {
    return true;
  }

  return order.profit < 0;
}

#endif
