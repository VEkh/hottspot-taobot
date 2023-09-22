#ifndef ML__FIVE_MIN_PREDICT
#define ML__FIVE_MIN_PREDICT

#include "five_min_predict.h" // ML::FiveMinPredict
#include "lib/pg/pg.cpp"      // Pg
#include <string>             // std::string

#include "get_fresh_predictions.cpp"
#include "log_predictions.cpp"
#include "predict.cpp"

ML::FiveMinPredict::FiveMinPredict(const Pg conn_, const std::string symbol_) {
  this->conn = conn_;
  this->symbol = symbol_;

  this->db_five_min_prediction =
      DB::FiveMinPrediction(this->conn, this->symbol);
}

#endif
