#ifndef ML__CANDLE_PREDICT_get_fresh_predictions
#define ML__CANDLE_PREDICT_get_fresh_predictions

#include "candle_predict.h" // ML::CandlePredict, prediction_t
#include <list>             // std::list
#include <map>              // std::map

void ML::CandlePredict::get_fresh_predictions(const double ref_epoch,
                                              const bool debug = false) {
  std::map<double, predictions_t> new_predictions;

  const std::list<prediction_t> fresh_predictions =
      this->db_candle_prediction.get_fresh_predictions(ref_epoch, debug);

  for (const prediction_t prediction : fresh_predictions) {
    new_predictions[prediction.candle.closed_at].predictions.push_back(
        prediction);
  }

  this->predictions = new_predictions;
}

#endif
