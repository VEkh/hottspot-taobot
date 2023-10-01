#ifndef ML__FIVE_MIN_PREDICT
#define ML__FIVE_MIN_PREDICT

#include "five_min_predict.h"                         // ML::FiveMinPredict
#include "db/candle/candle.cpp"                       // DB::Candle
#include "db/candle_prediction/candle_prediction.cpp" // DB::CandlePrediction
#include "lib/pg/pg.cpp"                              // Pg
#include <string>                                     // std::string

#include "get_fresh_predictions.cpp"
#include "log_predictions.cpp"
#include "predict.cpp"
#include "predict_action.cpp"
#include "should_close_position.cpp"
#include "should_predict.cpp"

ML::FiveMinPredict::FiveMinPredict(Pg conn_, const std::string symbol_) {
  this->db_env = conn_.flags["env"];
  this->symbol = symbol_;

  this->db_candle = DB::Candle(conn_, 5, this->symbol);
  this->db_candle_prediction = DB::CandlePrediction(conn_, 5, this->symbol);
}

#endif
