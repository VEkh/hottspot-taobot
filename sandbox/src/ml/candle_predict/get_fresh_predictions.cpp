#ifndef ML__CANDLE_PREDICT_get_fresh_predictions
#define ML__CANDLE_PREDICT_get_fresh_predictions

#include "candle_predict.h" // ML::CandlePredict

void ML::CandlePredict::get_fresh_predictions(const double ref_epoch,
                                              const bool debug = false) {
  this->predictions =
      this->db_candle_prediction.get_fresh_predictions(ref_epoch, debug);
}

#endif
