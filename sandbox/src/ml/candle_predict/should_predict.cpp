#ifndef ML__CANDLE_PREDICT_should_predict
#define ML__CANDLE_PREDICT_should_predict

#include "candle_predict.h" // ML::CandlePredict

bool ML::CandlePredict::should_predict(const bool does_position_exist = false) {
  if (!this->config.enabled) {
    return false;
  }

  if (this->config.hold_winning_prediction && does_position_exist) {
    return false;
  }

  return true;
}

#endif
