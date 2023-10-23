#ifndef ML__CANDLE_PREDICT_is_next_position_long
#define ML__CANDLE_PREDICT_is_next_position_long

#include "candle_predict.h"   // ML::CandlePredict, order_action_t
#include "predict_action.cpp" // predict_action

bool ML::CandlePredict::is_next_position_long() {
  return predict_action() == order_action_t::BUY;
}

#endif
