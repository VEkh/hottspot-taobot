#ifndef ML__CANDLE_PREDICT_set_consolidation_range
#define ML__CANDLE_PREDICT_set_consolidation_range

#include "candle_predict.h"   // ML::CandlePredict, order_action_t, prediction_t
#include "predict_action.cpp" // predict_action
#include <algorithm>          // std::max, std::min
#include <iterator>           // std::next
#include <list>               // std::list

void ML::CandlePredict::set_consolidation_range() {
  std::map<double, std::list<prediction_t>>::reverse_iterator it, next;

  for (it = this->correct_predictions.rbegin();
       it != this->correct_predictions.rend(); it++) {
    next = std::next(it);

    if (next == this->correct_predictions.rend()) {
      break;
    }

    const order_action_t predicted_action = predict_action(it->second);
    const order_action_t next_predicted_action = predict_action(next->second);

    if (predicted_action != next_predicted_action) {
      const double current_close = it->second.front().candle.close;
      const double next_close = next->second.front().candle.close;

      const double high = std::max(current_close, next_close);
      const double high_at = high == current_close ? it->first : next->first;
      const double low = std::min(current_close, next_close);
      const double low_at = low == current_close ? it->first : next->first;

      this->consolidation_range = {
          .high = high,
          .high_at = high_at,
          .low = low,
          .low_at = low_at,
      };

      break;
    }
  }
}

#endif
