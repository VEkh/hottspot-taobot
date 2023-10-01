#ifndef DB__CANDLE_PREDICTION_H
#define DB__CANDLE_PREDICTION_H

#include "db/candle/candle.cpp" // DB::Candle
#include "lib/pg/pg.cpp"        // Pg
#include <list>                 // std::list
#include <string>               // std::string

namespace DB {
class CandlePrediction {
public:
  using candle_t = DB::Candle::candle_t;

  struct prediction_t {
    candle_t candle;
    double close;
    double high;
    double low;
    std::string model_name;
    double open;
    std::string symbol;
  };

  CandlePrediction(){};
  CandlePrediction(const Pg, const int, const std::string);

  std::list<prediction_t> get_fresh_predictions(const double, const bool);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;
  int duration_minutes;
  std::string symbol;

  std::list<prediction_t> result_to_predictions(const query_result_t &);
};
} // namespace DB

#endif
