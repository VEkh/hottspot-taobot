#ifndef ML__CANDLE_PREDICT_H
#define ML__CANDLE_PREDICT_H

#include "db/candle/candle.cpp"                       // DB::Candle
#include "db/candle_prediction/candle_prediction.cpp" // DB::CandlePrediction
#include "lib/formatted.cpp"                          // Formatted
#include "lib/pg/pg.cpp"                              // Pg
#include "types.cpp"                                  // Global::t
#include <list>                                       // std::list
#include <map>                                        // std::map
#include <string>                                     // std::string
#include <utility>                                    // std::pair

namespace ML {
class CandlePredict {
public:
  using candle_predict_config_t = Global::t::candle_predict_config_t;
  using order_action_t = Global::t::order_action_t;
  using prediction_t = DB::CandlePrediction::prediction_t;

  CandlePredict(){};
  CandlePredict(Pg, const candle_predict_config_t, const int,
                const std::string);

  DB::Candle db_candle;
  DB::CandlePrediction db_candle_prediction;
  int duration_minutes;
  std::map<double, std::list<prediction_t>> predictions;

  bool is_ready_to_predict();
  bool should_close_position(const order_action_t);
  bool should_on_demand_predict();
  bool should_predict();

  order_action_t predict_action();
  order_action_t predict_action(const prediction_t);

  void get_fresh_predictions(const double, const bool);
  void log_predictions(const double);
  void predict(const double);

private:
  Formatted::fmt_stream_t fmt = Formatted::stream();
  candle_predict_config_t config;
  std::string db_env;
  std::string symbol;

  std::pair<double, std::list<prediction_t>> latest_predictions();
};
} // namespace ML

#endif
