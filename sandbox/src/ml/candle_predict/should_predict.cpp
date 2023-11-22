#ifndef ML__CANDLE_PREDICT_should_predict
#define ML__CANDLE_PREDICT_should_predict

#include "candle_predict.h" // ML::CandlePredict

bool ML::CandlePredict::should_predict() { return this->config.enabled; }

#endif
