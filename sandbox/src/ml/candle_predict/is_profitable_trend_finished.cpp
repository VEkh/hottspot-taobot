#ifndef ML__CANDLE_PREDICT_is_profitable_trend_finished
#define ML__CANDLE_PREDICT_is_profitable_trend_finished

#include "candle_predict.h" // ML::CandlePredict, order_action_t

bool ML::CandlePredict::is_profitable_trend_finished(
    const double current_mid, const order_action_t open_order_action) {
  if (this->opposing_predictions.size() < this->OPPOSING_PREDICTIONS_LIMIT) {
    return false;
  }

  const double deciding_opposing_prediction_close =
      this->opposing_predictions.begin()->second.front().candle.close;

  if (open_order_action == order_action_t::BUY &&
      current_mid < deciding_opposing_prediction_close) {
    return true;
  }

  if (open_order_action == order_action_t::SELL &&
      current_mid > deciding_opposing_prediction_close) {
    return true;
  }

  return false;
}

#endif
