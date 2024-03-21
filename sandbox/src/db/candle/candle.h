#ifndef DB__CANDLE_H
#define DB__CANDLE_H

#include "db/quote/quote.cpp" // DB::Quote
#include "db/utils/utils.cpp" // DB::Utils
#include "lib/formatted.cpp"  // Formatted
#include "lib/pg/pg.cpp"      // Pg
#include "types.cpp"          // Global::t
#include <list>               // std::list
#include <math.h>             // INFINITY
#include <string>             // std::string

namespace DB {
class Candle {
public:
  using trend_t = Global::t::trend_t;

  struct candle_bounds_t {
    double closed_at;
    double opened_at;
  };

  struct candle_t {
    double close = 0;
    double closed_at = 0;
    double high = -INFINITY;
    double low = INFINITY;
    double open = 0;
    double opened_at = 0;
    std::string symbol;

    double range() { return this->high - this->low; };

    trend_t trend() {
      if (this->close > this->open) {
        return trend_t::TREND_UP;
      }

      if (this->close < this->open) {
        return trend_t::TREND_DOWN;
      }

      return trend_t::TREND_CONSOLIDATION;
    };
  };

  struct get_latest_args_t {
    bool debug = false; // Optional
    double end_at_epoch;
    double start_at_epoch;
  };

  Candle(){};
  Candle(const Pg, const int, const std::string);
  int duration_minutes = 0; // TODO: Decide (Promotion to public)

  static candle_bounds_t timestamp_to_bounds(const int, const long int);

  std::list<candle_t> get_latest(const get_latest_args_t);

  void build();

private:
  using query_result_t = Pg::query_result_t;
  using quote_t = Global::t::quote_t;

  DB::Quote db_quote;
  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;
  std::string symbol;

  std::list<candle_t> result_to_candles(const query_result_t &);
  std::list<quote_t> get_latest_quotes(const bool);

  void upsert(const candle_t, const bool);
};
} // namespace DB

#endif
