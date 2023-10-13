#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "is_market_open.cpp"          // is_market_open
#include "should_ml_open_position.cpp" // should_ml_open_position
#include "tao_bot.h"                   // Alpaca::TaoBot

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

  if (this->five_min_predict.should_predict()) {
    return should_ml_open_position(this->five_min_predict);
  }

  return true;
}

#endif
