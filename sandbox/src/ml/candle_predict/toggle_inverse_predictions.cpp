#ifndef ML__CANDLE_PREDICT_toggle_inverse_predictions
#define ML__CANDLE_PREDICT_toggle_inverse_predictions

#include "candle_predict.h" // ML::CandlePredict

void ML::CandlePredict::toggle_inverse_predictions() {
  toggle_inverse_predictions(!this->config.inverse_predictions);
}

void ML::CandlePredict::toggle_inverse_predictions(const bool value) {
  this->config.inverse_predictions = value;
}

#endif
