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
  using candle_t = DB::Candle::candle_t;
  using candle_predict_config_t = Global::t::candle_predict_config_t;
  using order_action_t = Global::t::order_action_t;
  using prediction_t = DB::CandlePrediction::prediction_t;

  CandlePredict(){};
  CandlePredict(Pg, const candle_predict_config_t, const std::string);

  struct should_close_position_args_t {
    double current_epoch;
    order_action_t open_order_action;
    double open_order_max_profit;
    double open_order_opened_at;
    double open_order_profit;
    double open_order_stop_profit;
  };

  candle_predict_config_t config;
  int duration_minutes;

  bool are_predictions_stale(const double);
  bool is_next_position_long();
  bool is_ready_to_predict(const double);
  bool should_close_position(const should_close_position_args_t);
  bool should_on_demand_predict();
  bool should_predict();

  order_action_t predict_action();
  order_action_t predict_action(const prediction_t);
  order_action_t predict_action(const std::list<prediction_t>);
  order_action_t predict_action(const std::list<prediction_t>,
                                const std::string);

  void get_fresh_predictions(const double, const bool);
  void log_correct_predictions();
  void log_predictions(const double);
  void predict(const double);
  void toggle_inverse_predictions();
  void toggle_inverse_predictions(const bool);

private:
  constexpr static int TREND_WINDOW_SIZE = 4;

  struct consolidation_range_t {
    double high;
    double high_at;
    double low;
    double low_at;
  };

  DB::Candle db_candle;
  DB::CandlePrediction db_candle_prediction;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::map<double, std::list<prediction_t>> correct_predictions;
  std::map<double, std::list<prediction_t>> predictions;
  std::string db_env;
  std::string symbol;

  bool has_been_predicting_since(const double);

  double latest_opposite_prediction_closed_at(
      std::map<double, std::list<prediction_t>>, const order_action_t);

  std::pair<double, std::list<prediction_t>> latest_predictions();
};
} // namespace ML

#endif
