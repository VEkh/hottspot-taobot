#ifndef ML__FIVE_MIN_PREDICT_predict_action
#define ML__FIVE_MIN_PREDICT_predict_action

#include "five_min_predict.h" // ML::FiveMinPredict

ML::FiveMinPredict::order_action_t ML::FiveMinPredict::predict_action() {
  prediction_t deciding_prediction;

  for (const prediction_t prediction : this->predictions) {
    if (prediction.model_name == "lstm") {
      deciding_prediction = prediction;
    }
  }

  return predict_action(deciding_prediction);
}

ML::FiveMinPredict::order_action_t
ML::FiveMinPredict::predict_action(const prediction_t prediction) {
  if (prediction.close < prediction.candle.close) {
    return order_action_t::SELL;
  }

  return order_action_t::BUY;
}

#endif
