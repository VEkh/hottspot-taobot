#ifndef DB__FIVE_MIN_PREDICTION
#define DB__FIVE_MIN_PREDICTION

#include "five_min_prediction.h" // DB::FiveMinPrediction
#include "get_fresh_predictions.cpp"
#include "lib/pg/pg.cpp" // Pg

DB::FiveMinPrediction::FiveMinPrediction(const Pg conn_,
                                         const std::string symbol_) {
  this->conn = conn_;
  this->symbol = symbol_;
}

#endif
