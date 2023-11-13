#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "is_market_open.cpp"          // is_market_open
#include "should_ml_open_position.cpp" // should_ml_open_position
#include "tao_bot.h"                   // Alpaca::TaoBot
#include "volatility.cpp"              // volatility

bool Alpaca::TaoBot::should_open_position() {
  if (!is_market_open()) {
    return false;
  }

  if (this->open_order_ptr) {
    return false;
  }

  if (!this->avg_one_sec_variances.latest) {
    return false;
  }

  if (this->closed_positions.empty() &&
      this->candle_predictor.should_predict(volatility())) {
    return should_ml_open_position(this->candle_predictor);
  }

  return true;
}

#endif
