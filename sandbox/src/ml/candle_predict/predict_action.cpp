#ifndef ML__CANDLE_PREDICT_predict_action
#define ML__CANDLE_PREDICT_predict_action

#include "candle_predict.h"       // ML::CandlePredict, prediction_t
#include "latest_predictions.cpp" // latest_predictions
#include <list>                   // std::list

ML::CandlePredict::order_action_t ML::CandlePredict::predict_action() {
  int buy_count = 0;
  int sell_count = 0;
  std::list<prediction_t> latest_predictions_ = latest_predictions().second;

  for (const prediction_t prediction : latest_predictions_) {
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

ML::CandlePredict::order_action_t
ML::CandlePredict::predict_action(const prediction_t prediction) {
  if (prediction.close < prediction.candle.close) {
    return order_action_t::SELL;
  }

  return order_action_t::BUY;
}

#endif
