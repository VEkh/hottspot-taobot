#ifndef ML__FIVE_MIN_PREDICT_should_close_position
#define ML__FIVE_MIN_PREDICT_should_close_position

#include "five_min_predict.h" // ML::FiveMinPredict
#include "predict_action.cpp" // predict_action

bool ML::FiveMinPredict::should_close_position(
    const order_action_t open_order_action) {
  if (this->predictions.empty()) {
    return false;
  }

  const order_action_t predicted_action = predict_action();

  return predicted_action != open_order_action;
}

#endif
