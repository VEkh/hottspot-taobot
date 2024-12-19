#ifndef OANDA__TAO_BOT_should_stop_profit
#define OANDA__TAO_BOT_should_stop_profit

#include "is_trend_slipping.cpp"     // is_trend_slipping
#include "latest_reversal_after.cpp" // latest_reversal_after
#include "tao_bot.h"                 // Oanda::TaoBot, reversal_t

bool Oanda::TaoBot::should_stop_profit() {
  if (!this->api_client.config.should_stop_profit) {
    return false;
  }

  if (!this->open_order_ptr) {
    return false;
  }

  const stop_profit_type_t stop_profit_type =
      this->open_order_ptr->stop_profit_type;

  if (stop_profit_type != stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE &&
      stop_profit_type != stop_profit_type_t::STOP_PROFIT_CROSS_RANGE) {
    return false;
  }

  if (this->exit_prices.stop_profit &&
      this->open_order_ptr->max_profit < this->exit_prices.stop_profit) {
    return false;
  }

  if (!is_trend_slipping(this->open_order_ptr)) {
    return false;
  }

  return true;
}

#endif
