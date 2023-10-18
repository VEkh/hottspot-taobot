#ifndef ML__CANDLE_PREDICT_get_fresh_predictions
#define ML__CANDLE_PREDICT_get_fresh_predictions

#include "candle_predict.h"   // ML::CandlePredict, order_action_t, prediction_t
#include "predict_action.cpp" // predict_action
#include <iterator>           // std::next
#include <list>               // std::list
#include <map>                // std::map

void ML::CandlePredict::get_fresh_predictions(const double ref_epoch,
                                              const bool debug = false) {
  this->correct_predictions = {};
  this->predictions = {};

  std::map<double, std::list<prediction_t>> new_predictions;

  const std::list<prediction_t> fresh_predictions =
      this->db_candle_prediction.get_fresh_predictions(ref_epoch, debug);

  for (const prediction_t prediction : fresh_predictions) {
    new_predictions[prediction.candle.closed_at].push_back(prediction);
  }

  std::map<double, std::list<prediction_t>>::iterator it, next;

  for (it = new_predictions.begin(); it != new_predictions.end(); it++) {
    next = std::next(it);

    if (next == new_predictions.end()) {
      continue;
    }

    const double current_close = it->second.front().candle.close;
    const double next_close = next->second.front().candle.close;

    const order_action_t predicted_action = predict_action(it->second);

    const bool is_correct = (predicted_action == order_action_t::BUY &&
                             next_close > current_close) ||
                            (predicted_action == order_action_t::SELL &&
                             next_close < current_close);

    if (is_correct) {
      this->correct_predictions[it->first] = it->second;
    }
  }

  this->predictions = new_predictions;
}

#endif
