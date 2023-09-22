#ifndef ML__FIVE_MIN_PREDICT_H
#define ML__FIVE_MIN_PREDICT_H

#include "db/five_min_prediction/five_min_prediction.cpp" // DB::FiveMinPrediction
#include "lib/formatted.cpp"                              // Formatted
#include "lib/pg/pg.cpp"                                  // Pg
#include <list>                                           // std::list
#include <string>                                         // std::string

namespace ML {
class FiveMinPredict {
public:
  using prediction_t = DB::FiveMinPrediction::prediction_t;

  FiveMinPredict(){};
  FiveMinPredict(const Pg, const std::string);

  DB::FiveMinPrediction db_five_min_prediction;
  std::list<prediction_t> predictions;

  void get_fresh_predictions(const double);
  void log_predictions();
  void predict(const double);

private:
  Formatted::fmt_stream_t fmt = Formatted::stream();
  // TODO: Remove from here and reference db_five_min_prediction's env
  Pg conn;
  std::string symbol;
};
} // namespace ML

#endif
