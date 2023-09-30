#ifndef ML__FIVE_MIN_PREDICT_predict_action
#define ML__FIVE_MIN_PREDICT_predict_action

#include "five_min_predict.h" // ML::FiveMinPredict

ML::FiveMinPredict::order_action_t ML::FiveMinPredict::predict_action() {
  int buy_count = 0;
  int sell_count = 0;

  for (const prediction_t prediction : this->predictions) {
    switch (predict_action(prediction)) {
    case order_action_t::BUY: {
      buy_count += 1;
      break;
    }
    case order_action_t::SELL: {
      sell_count += 1;
      break;
    }
    }
  }

  if (buy_count >= sell_count) {
    return order_action_t::BUY;
  }

  return order_action_t::SELL;
}

ML::FiveMinPredict::order_action_t
ML::FiveMinPredict::predict_action(const prediction_t prediction) {
  if (prediction.close < prediction.candle.close) {
    return order_action_t::SELL;
  }

  return order_action_t::BUY;
}

#endif
