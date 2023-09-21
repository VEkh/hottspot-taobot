#ifndef DB__FIVE_MIN_PREDICTION_H
#define DB__FIVE_MIN_PREDICTION_H

#include "lib/pg/pg.cpp" // Pg
#include <list>          // std::list
#include <string>        // std::string

namespace DB {
class FiveMinPrediction {
public:
  struct prediction_t {
    double close;
    double high;
    double inserted_at;
    double low;
    std::string model_name;
    double open;
    std::string symbol;
  };

  FiveMinPrediction(const Pg, const std::string);

  std::list<prediction_t> get_fresh_predictions(const double, const bool);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;
  std::string symbol;

  std::list<prediction_t> result_to_predictions(const query_result_t &);
};
} // namespace DB

#endif
