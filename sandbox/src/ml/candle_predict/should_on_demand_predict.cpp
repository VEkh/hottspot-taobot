#ifndef ML__CANDLE_PREDICT_should_on_demand_predict
#define ML__CANDLE_PREDICT_should_on_demand_predict

#include "candle_predict.h" // ML::CandlePredict

bool ML::CandlePredict::should_on_demand_predict() {
  return this->config.on_demand_predictions;
}

#endif
