#ifndef ML__CANDLE_PREDICT_get_trend_candles
#define ML__CANDLE_PREDICT_get_trend_candles

#include "candle_predict.h" // ML::CandlePredict

void ML::CandlePredict::get_trend_candles(const double current_epoch) {
  this->trend_candles = this->db_candle.get_latest({
      .end_at_epoch = current_epoch,
      .limit = this->TREND_WINDOW_SIZE,
  });
}

#endif
