#ifndef ML__FIVE_MIN_PREDICT_get_fresh_predictions
#define ML__FIVE_MIN_PREDICT_get_fresh_predictions

#include "five_min_predict.h" // ML::FiveMinPredict

void ML::FiveMinPredict::get_fresh_predictions(const double ref_epoch,
                                               const bool debug = false) {
  this->predictions =
      this->db_five_min_prediction.get_fresh_predictions(ref_epoch, debug);
}

#endif
