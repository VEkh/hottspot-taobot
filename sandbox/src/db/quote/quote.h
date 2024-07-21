#ifndef DB__QUOTE_H
#define DB__QUOTE_H

#include "db/utils/utils.h" // DB::Utils
#include "lib/pg/pg.h"      // Pg
#include "types.cpp"        // Global::t
#include <list>             // std::list
#include <string>           // std::string

namespace DB {
class Quote {
public:
  using avg_one_sec_variances_t = Global::t::avg_one_sec_variances_t;
  using query_result_t = Pg::query_result_t;
  using quote_t = Global::t::quote_t;

  static constexpr double CACHE_DURATION_SECONDS = 60 * 60;

  struct cache_t {
    std::list<quote_t> cache;
    double expires_at = 0;
    double set_at = 0;

    bool is_expired(const double epoch) {
      if (this->cache.empty()) {
        return true;
      }

      return epoch >= this->expires_at;
    }
  };

  struct get_last_args_t {
    bool debug = false;
    double end_at;
    int limit = 0;
    long int limit_offset = 0;
    bool read_cache = false;
    std::string sort_direction = "desc";
    double start_at = 0.0;
    std::string symbol;
    bool write_cache = false;
  };

  struct get_avg_one_sec_variances_args_t {
    bool debug = false;
    std::string symbol;
    double end_at;
  };

  struct upsert_avg_one_sec_variance_args_t {
    bool debug = true;
    long int id = 0;
    std::string symbol;
  };

  struct upsert_all_avg_one_sec_variances_args_t {
    bool debug = false;
    std::string end_at;
    std::string start_at;
    std::string symbol;
  };

  Quote(){};
  Quote(Pg c);

  cache_t cache;

  avg_one_sec_variances_t
  get_avg_one_sec_variances(const get_avg_one_sec_variances_args_t);

  std::list<quote_t> get(const std::string, const double);
  std::list<quote_t> get_last(const get_last_args_t);
  std::list<quote_t> result_to_quotes(const query_result_t &);

  void clear_cache() { this->cache = cache_t(); }; // TODO: Decide
  void upsert(const quote_t);
  void upsert(const std::list<quote_t>);
  void upsert_all_avg_one_sec_variances(
      const upsert_all_avg_one_sec_variances_args_t);
  void upsert_avg_one_sec_variance(const upsert_avg_one_sec_variance_args_t);

private:
  DB::Utils db_utils;
  Pg conn;

  double result_to_stop_profit(const query_result_t &);

  avg_one_sec_variances_t
  result_to_avg_one_sec_variances(const query_result_t &);

  std::list<quote_t> get_last_from_cache(const get_last_args_t);
  std::list<quote_t> get_last_from_db(const get_last_args_t);
};
} // namespace DB

#endif
