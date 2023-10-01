#ifndef DB__CANDLE_PREDICTION
#define DB__CANDLE_PREDICTION

#include "candle_prediction.h" // DB::CandlePrediction
#include "get_fresh_predictions.cpp"
#include "lib/pg/pg.cpp" // Pg
#include <string>        // std::string

DB::CandlePrediction::CandlePrediction(const Pg c, const int dm,
                                       const std::string s) {
  this->conn = c;
  this->duration_minutes = dm;
  this->symbol = s;
}

#endif
