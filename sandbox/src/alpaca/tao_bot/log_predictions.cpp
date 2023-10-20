#ifndef ALPACA__TAO_BOT_log_predictions
#define ALPACA__TAO_BOT_log_predictions

#include "current_mid.cpp"           // current_mid
#include "excess_trigger_buffer.cpp" // excess_trigger_buffer
#include "tao_bot.h"                 // Alpaca::TaoBot

void Alpaca::TaoBot::log_predictions() {
  if (!this->candle_predictor.should_predict()) {
    return;
  }

  this->candle_predictor.log_predictions(this->current_epoch);
  this->candle_predictor.log_correct_predictions();
  this->candle_predictor.log_consolidation_range({
      .current_mid = current_mid(),
      .range_buffer = excess_trigger_buffer(),
  });
}

#endif
