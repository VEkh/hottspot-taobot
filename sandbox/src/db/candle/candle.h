#ifndef DB__CANDLE_H
#define DB__CANDLE_H

#include "db/quote/quote.cpp" // DB::Quote
#include "db/utils/utils.cpp" // DB::Utils
#include "lib/formatted.cpp"  // Formatted
#include "lib/pg/pg.cpp"      // Pg
#include "types.cpp"          // Global::t
#include <list>               // std::list
#include <string>             // std::string

namespace DB {
class Candle {
public:
  using candle_t = Global::t::candle_t;

  struct candle_bounds_t {
    double closed_at;
    double opened_at;
  };

  struct build_args_t {
    bool debug = false; // Optional
    std::string end_at;
    std::string start_at;
  };

  struct get_build_quotes_args_t {
    bool debug = false; // Optional
    double end_at = 0.0;
    int limit = 0;
    double start_at = 0.0;
  };

  struct get_latest_args_t {
    bool debug = false; // Optional
    double end_at = 0.0;
    bool read_cache = false;
    double start_at = 0.0;
    bool write_cache = false;
  };

  struct time_range_args_t {
    bool debug = false; // Optional
    double end_at = 0.0;
    double start_at = 0.0;
  };

  Candle(){};
  Candle(const Pg, const int, const std::string);

  std::list<candle_t> cache;

  static candle_bounds_t timestamp_to_bounds(const int, const long int);

  int duration_minutes = 0;

  std::list<candle_t> get_latest(const get_latest_args_t);

  void build(const build_args_t);

  void clear_cache() { this->cache = {}; };

private:
  using query_result_t = Pg::query_result_t;
  using quote_t = Global::t::quote_t;

  DB::Quote db_quote;
  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;
  std::string symbol;

  double get_default_build_start_at(const bool);

  std::list<candle_t> get_latest_from_cache(const get_latest_args_t);
  std::list<candle_t> get_latest_from_db(const get_latest_args_t);

  std::list<candle_t> result_to_candles(const query_result_t &);
  std::list<quote_t> batch_get_build_quotes(const time_range_args_t);
  std::list<quote_t> get_build_quotes(const get_build_quotes_args_t);

  void print_build_intro(const time_range_args_t);
  void upsert(const candle_t, const bool);
};
} // namespace DB

#endif
