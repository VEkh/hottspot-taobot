#ifndef DB__CANDLE_H
#define DB__CANDLE_H

#include "db/quote/quote.cpp" // DB::Quote
#include "lib/formatted.cpp"  // Formatted
#include "lib/pg/pg.cpp"      // Pg
#include "types.cpp"          // Global::t
#include <list>               // std::list
#include <math.h>             // INFINITY
#include <string>             // std::string

namespace DB {
class Candle {
public:
  struct candle_t {
    double close = 0;
    double closed_at = 0;
    double high = -INFINITY;
    double low = INFINITY;
    double open = 0;
    double opened_at = 0;
    std::string symbol;
  };

  Candle(){};
  Candle(const Pg, const int, const std::string);

  void build();

private:
  using query_result_t = Pg::query_result_t;
  using quote_t = Global::t::quote_t;

  struct candle_bounds_t {
    double closed_at;
    double opened_at;
  };

  DB::Quote db_quote;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;
  int duration_minutes = 0;
  std::string symbol;

  candle_bounds_t quote_to_bounds(const quote_t &);

  std::list<quote_t> get_latest_quotes(const bool);

  void upsert(const candle_t, const bool);
};
} // namespace DB

#endif
