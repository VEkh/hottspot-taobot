#ifndef DB__FIVE_MIN_PREDICTION_H
#define DB__FIVE_MIN_PREDICTION_H

#include "db/five_min_candle/five_min_candle.cpp" // DB::FiveMinCandle
#include "lib/pg/pg.cpp"                          // Pg
#include <list>                                   // std::list
#include <string>                                 // std::string

namespace DB {
class FiveMinPrediction {
public:
  using candle_t = DB::FiveMinCandle::candle_t;

  constexpr static int EXIRATION_SECONDS = 5 * 60;

  struct prediction_t {
    candle_t candle;
    double close;
    double high;
    double low;
    std::string model_name;
    double open;
    std::string symbol;
  };

  FiveMinPrediction(){};
  FiveMinPrediction(const Pg c, const std::string s) : conn(c), symbol(s){};

  std::list<prediction_t> get_fresh_predictions(const double, const bool);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;
  std::string symbol;

  std::list<prediction_t> result_to_predictions(const query_result_t &);
};
} // namespace DB

#endif
