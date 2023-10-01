#ifndef ML__CANDLE_PREDICT_predict_action
#define ML__CANDLE_PREDICT_predict_action

#include "candle_predict.h" // ML::CandlePredict

// TODO: Remove when done experimenting
// ML::CandlePredict::order_action_t ML::CandlePredict::predict_action() {
//   prediction_t deciding_prediction;

//   for (const prediction_t prediction : this->predictions) {
//     if (prediction.model_name == "lstm") {
//       deciding_prediction = prediction;
//     }
//   }

//   return predict_action(deciding_prediction);
// }

ML::CandlePredict::order_action_t ML::CandlePredict::predict_action() {
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

ML::CandlePredict::order_action_t
ML::CandlePredict::predict_action(const prediction_t prediction) {
  if (prediction.close < prediction.candle.close) {
    return order_action_t::SELL;
  }

  return order_action_t::BUY;
}

#endif
