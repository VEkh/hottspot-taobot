#ifndef ML__CANDLE_PREDICT_should_predict
#define ML__CANDLE_PREDICT_should_predict

#include "candle_predict.h" // ML::CandlePredict

bool ML::CandlePredict::should_predict(const double volatility = 0) {
  if (volatility && volatility < 2.0) {
    return false;
  }

  return this->config.enabled;
}

#endif
