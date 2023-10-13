#ifndef ML__CANDLE_PREDICT_get_fresh_predictions
#define ML__CANDLE_PREDICT_get_fresh_predictions

#include "candle_predict.h"   // ML::CandlePredict, order_action_t, prediction_t
#include "predict_action.cpp" // predict_action
#include <iterator>           // std::next
#include <list>               // std::list
#include <map>                // std::map

void ML::CandlePredict::get_fresh_predictions(const double ref_epoch,
                                              const bool debug = false) {
  std::map<double, predictions_t> new_predictions;

  const std::list<prediction_t> fresh_predictions =
      this->db_candle_prediction.get_fresh_predictions(ref_epoch, debug);

  for (const prediction_t prediction : fresh_predictions) {
    new_predictions[prediction.candle.closed_at].predictions.push_back(
        prediction);
  }

  std::map<double, predictions_t>::iterator it;

  for (it = new_predictions.begin(); it != new_predictions.end(); it++) {
    if (std::next(it) == new_predictions.end()) {
      continue;
    }

    const double current_close = it->second.predictions.front().candle.close;

    const double next_close =
        std::next(it)->second.predictions.front().candle.close;

    const order_action_t predicted_action =
        predict_action(it->second.predictions);

    it->second.is_correct = (predicted_action == order_action_t::BUY &&
                             next_close > current_close) ||
                            (predicted_action == order_action_t::SELL &&
                             next_close < current_close);
  }

  this->predictions = new_predictions;
}

#endif
