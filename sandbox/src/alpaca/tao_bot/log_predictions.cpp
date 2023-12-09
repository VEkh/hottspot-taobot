#ifndef ALPACA__TAO_BOT_log_predictions
#define ALPACA__TAO_BOT_log_predictions

#include "current_mid.cpp"         // current_mid
#include "does_position_exist.cpp" // does_position_exist
#include "tao_bot.h"               // Alpaca::TaoBot

void Alpaca::TaoBot::log_predictions() {
  if (!this->candle_predictor.should_predict(does_position_exist())) {
    return;
  }

  this->candle_predictor.log_predictions(this->current_epoch);
  this->candle_predictor.log_correct_predictions();
}

#endif
