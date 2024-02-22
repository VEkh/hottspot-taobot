#ifndef ALPACA__TAO_BOT_should_open_position
#define ALPACA__TAO_BOT_should_open_position

#include "does_position_exist.cpp"     // does_position_exist
#include "is_market_open.cpp"          // is_market_open
#include "should_ml_open_position.cpp" // should_ml_open_position
#include "tao_bot.h"                   // Alpaca::TaoBot

#include "is_entry_signal_present.cpp" // is_entry_signal_present // TODO: Decide

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

  if (this->candle_predictor.should_predict(does_position_exist())) {
    if (this->closed_positions.empty()) {
      return this->candle_predictor.is_ready_to_predict(this->current_epoch);
    }

    if (!this->candle_predictor.config.rollover_positions) {
      return should_ml_open_position(this->candle_predictor);
    }
  }

  if (this->api_client.config.should_await_reversal_indicator) {
    return is_entry_signal_present();
  }

  return true;
}

#endif
