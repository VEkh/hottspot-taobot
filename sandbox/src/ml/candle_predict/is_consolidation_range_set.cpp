#ifndef ML__CANDLE_PREDICT_is_consolidation_range_set
#define ML__CANDLE_PREDICT_is_consolidation_range_set

#include "candle_predict.h" // ML::CandlePredict

bool ML::CandlePredict::is_consolidation_range_set() {
  return this->consolidation_range.high && this->consolidation_range.low;
}

#endif
