#ifndef ML__CANDLE_PREDICT_current_trend
#define ML__CANDLE_PREDICT_current_trend

#include "candle_predict.h" // ML::CandlePredict, candle_t, trend_t

ML::CandlePredict::trend_t ML::CandlePredict::current_trend() {
  if (this->trend_candles.size() < this->TREND_WINDOW_SIZE) {
    return trend_t::TREND_CONSOLIDATION;
  }

  int down_count = 0;
  int up_count = 0;

  for (candle_t candle : this->trend_candles) {
    down_count += candle.trend() == trend_t::TREND_DOWN;
    up_count += candle.trend() == trend_t::TREND_UP;
  }

  if (up_count > down_count) {
    return trend_t::TREND_UP;
  }

  if (down_count > up_count) {
    return trend_t::TREND_DOWN;
  }

  return trend_t::TREND_CONSOLIDATION;
}

#endif
