// TODO: Decide
#ifndef ALPACA__TAO_BOT_should_stop_profit
#define ALPACA__TAO_BOT_should_stop_profit

#include "is_trend_slipping.cpp"     // is_trend_slipping
#include "latest_reversal_after.cpp" // latest_reversal_after
#include "tao_bot.h"                 // Alpaca::TaoBot, reversal_t

bool Alpaca::TaoBot::should_stop_profit() {
  // TODO: Decide
  if (!this->api_client.config.should_stop_profit) {
    return false;
  }

  if (!this->open_order_ptr) {
    return false;
  }

  if (this->exit_prices.stop_profit &&
      this->open_order_ptr->max_profit < this->exit_prices.stop_profit) {
    return false;
  }

  if (this->open_order_ptr->profit < 0) {
    return false;
  }

  if (!is_trend_slipping(this->open_order_ptr)) {
    return false;
  }

  return true;
}

#endif
