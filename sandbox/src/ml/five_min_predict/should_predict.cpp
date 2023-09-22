#ifndef ML__FIVE_MIN_PREDICT_should_predict
#define ML__FIVE_MIN_PREDICT_should_predict

#include "five_min_predict.h" // ML::FiveMinPredict

bool ML::FiveMinPredict::should_predict(const std::string api_key) {
  return this->API_KEYS_WHITELIST[api_key];
}

#endif
