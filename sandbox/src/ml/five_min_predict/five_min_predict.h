#ifndef ML__FIVE_MIN_PREDICT_H
#define ML__FIVE_MIN_PREDICT_H

#include "db/five_min_candle/five_min_candle.cpp"         // DB::FiveMinCandle
#include "db/five_min_prediction/five_min_prediction.cpp" // DB::FiveMinPrediction
#include "lib/formatted.cpp"                              // Formatted
#include "lib/pg/pg.cpp"                                  // Pg
#include "types.cpp"                                      // Global::t
#include <list>                                           // std::list
#include <map>                                            // std::map
#include <string>                                         // std::string

namespace ML {
class FiveMinPredict {
public:
  using order_action_t = Global::t::order_action_t;
  using prediction_t = DB::FiveMinPrediction::prediction_t;

  std::map<std::string, bool> API_KEYS_WHITELIST = {
      {"backtest-ml", true},
      {"paper-alpha", true},
  };

  FiveMinPredict(){};
  FiveMinPredict(Pg, const std::string);

  DB::FiveMinCandle db_five_min_candle;
  DB::FiveMinPrediction db_five_min_prediction;
  std::list<prediction_t> predictions;

  bool should_close_position(const order_action_t);
  bool should_predict(const std::string);

  order_action_t predict_action();
  order_action_t predict_action(const prediction_t);

  void get_fresh_predictions(const double, const bool);
  void log_predictions();
  void predict(const double);

private:
  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::string db_env;
  std::string symbol;
};
} // namespace ML

#endif
