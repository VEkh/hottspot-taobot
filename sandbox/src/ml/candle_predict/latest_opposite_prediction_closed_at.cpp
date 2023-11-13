// TODO: Decide
#ifndef ML__CANDLE_PREDICT_latest_opposite_prediction_closed_at
#define ML__CANDLE_PREDICT_latest_opposite_prediction_closed_at

#include "candle_predict.h" // ML::CandlePredict, order_action_t, prediction_t
#include "is_ready_to_predict.cpp" // is_ready_to_predict
#include "predict_action.cpp"      // predict_action
#include <list>                    // std::list
#include <map>                     // std::map

double ML::CandlePredict::latest_opposite_prediction_closed_at(
    std::map<double, std::list<prediction_t>> predictions,
    const order_action_t open_order_action) {
  double latest_closed_at = 0;
  std::map<double, std::list<prediction_t>>::reverse_iterator it;

  for (it = predictions.rbegin(); it != predictions.rend(); it++) {
    const order_action_t predicted_action = predict_action(it->second);

    if (open_order_action != predicted_action) {
      latest_closed_at = it->first;

      break;
    }
  }

  return latest_closed_at;
}

#endif
