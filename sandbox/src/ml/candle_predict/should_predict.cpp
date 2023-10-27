#ifndef ML__CANDLE_PREDICT_should_predict
#define ML__CANDLE_PREDICT_should_predict

#include "candle_predict.h" // ML::CandlePredict

bool ML::CandlePredict::should_predict(const double volatility = 0) {
  if (!this->config.enabled) {
    return false;
  }

  if (!this->config.switch_to_momentum) {
    return true;
  }

  if (volatility && volatility < 2.5) {
    return false;
  }

  return true;
}

#endif
