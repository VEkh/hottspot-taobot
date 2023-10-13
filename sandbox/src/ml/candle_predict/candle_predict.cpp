#ifndef ML__CANDLE_PREDICT
#define ML__CANDLE_PREDICT

#include "candle_predict.h"                           // ML::CandlePredict
#include "db/candle/candle.cpp"                       // DB::Candle
#include "db/candle_prediction/candle_prediction.cpp" // DB::CandlePrediction
#include "lib/pg/pg.cpp"                              // Pg
#include <string>                                     // std::string

#include "are_predictions_stale.cpp"
#include "build_opposing_predictions.cpp"
#include "get_fresh_predictions.cpp"
#include "is_ready_to_predict.cpp"
#include "latest_predictions.cpp"
#include "log_correct_predictions.cpp"
#include "log_opposing_predictions.cpp"
#include "log_predictions.cpp"
#include "predict.cpp"
#include "predict_action.cpp"
#include "should_close_position.cpp"
#include "should_on_demand_predict.cpp"
#include "should_predict.cpp"

ML::CandlePredict::CandlePredict(Pg conn, const candle_predict_config_t conf,
                                 const int dm, const std::string s) {
  this->config = conf;
  this->db_env = conn.flags["env"];
  this->duration_minutes = dm;
  this->symbol = s;

  this->db_candle = DB::Candle(conn, this->duration_minutes, this->symbol);
  this->db_candle_prediction =
      DB::CandlePrediction(conn, this->duration_minutes, this->symbol);
}

#endif
