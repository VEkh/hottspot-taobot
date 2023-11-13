#ifndef ML__CANDLE_PREDICT_should_predict
#define ML__CANDLE_PREDICT_should_predict

#include "candle_predict.h" // ML::CandlePredict

bool ML::CandlePredict::should_predict() {
  if (!this->config.enabled) {
    return false;
  }

  if (!this->config.switch_to_momentum) {
    return true;
  }

  return true;
}

#endif
