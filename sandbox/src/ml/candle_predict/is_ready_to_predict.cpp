#ifndef ML__CANDLE_PREDICT_is_ready_to_predict
#define ML__CANDLE_PREDICT_is_ready_to_predict

#include "candle_predict.h" // ML::CandlePredict

bool ML::CandlePredict::is_ready_to_predict() {
  if (this->predictions.size() < 2) {
    return false;
  }

  return this->predictions.size() % 2 != 0;
}

#endif
