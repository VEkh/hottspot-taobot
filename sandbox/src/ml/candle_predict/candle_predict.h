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

  struct should_close_position_args_t {
    double current_mid;
    order_action_t open_order_action;
    double open_order_execution;
    double open_order_max_profit;
    double open_order_profit;
  };

  int duration_minutes;

  bool are_predictions_stale(const double);
  bool is_ready_to_predict();
  bool should_close_position(const should_close_position_args_t);
  bool should_on_demand_predict();
  bool should_predict();

  order_action_t predict_action();
  order_action_t predict_action(const prediction_t);
  order_action_t predict_action(const std::list<prediction_t>);

  void build_opposing_predictions(const order_action_t);
  void get_fresh_predictions(const double, const bool);
  void log_consolidation_range(const double);
  void log_correct_predictions();
  void log_opposing_predictions();
  void log_predictions(const double);
  void predict(const double);
  void set_consolidation_range();

private:
  constexpr static int OPPOSING_PREDICTIONS_LIMIT = 2;

  struct consolidation_range_t {
    double high;
    double high_at;
    double low;
    double low_at;
  };

  DB::Candle db_candle;
  DB::CandlePrediction db_candle_prediction;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  candle_predict_config_t config;
  consolidation_range_t consolidation_range;
  std::map<double, std::list<prediction_t>> correct_predictions;
  std::map<double, std::list<prediction_t>> opposing_predictions;
  std::map<double, std::list<prediction_t>> predictions;
  std::string db_env;
  std::string symbol;

  bool is_profitable_trend_finished(should_close_position_args_t);

  std::pair<double, std::list<prediction_t>> latest_predictions();
};
} // namespace ML

#endif
