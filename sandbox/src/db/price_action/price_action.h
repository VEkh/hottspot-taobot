#ifndef DB__PRICE_ACTION_H
#define DB__PRICE_ACTION_H

#include "db/quote/quote.cpp"                          // DB::Quote
#include "db/utils/utils.cpp"                          // DB::Utils
#include "lib/formatted.cpp"                           // Formatted
#include "lib/nyse_availability/nyse_availability.cpp" // NyseAvailability
#include "lib/pg/pg.cpp"                               // Pg
#include "types.cpp"                                   // Global::t
#include <string>                                      // std::string
#include <time.h>                                      // time

namespace DB {
class PriceAction {
public:
  using candle_t = Global::t::candle_t;
  using quote_t = Global::t::quote_t;

  struct build_args_t {
    std::string end_at;
    std::string start_at;
  };

  struct build_state_t {
    double avg_price_action = 0.0;
    candle_t day_candle;
    int days_n = 0;
    double end_at;
    double price_action_sum = 0.0;
    std::list<quote_t> quotes;
    double start_at;
    double timer_start;

    int duration() { return time(nullptr) - this->timer_start; };
  };

  struct get_stats_args_t {
    double end_at;
    int time_range_weeks;
  };

  struct init_args_t {
    Pg conn;
    bool debug = false;
    std::string symbol;
  };

  struct price_action_stats_t {
    double avg = 0.0;
    double std = 0.0;
  };

  PriceAction(const init_args_t);
  PriceAction(){};

  price_action_stats_t get_stats(const get_stats_args_t);

  void build(const build_args_t);

private:
  using query_result_t = Pg::query_result_t;

  DB::Quote db_quote;
  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  NyseAvailability market_availability;
  Pg conn;
  bool debug;
  build_state_t build_state;
  std::string symbol;

  price_action_stats_t result_to_stats(const query_result_t &);

  void init_build_state(const build_args_t);
  void log_build_summary(build_state_t &);
  void log_candle(candle_t &);
  void process_quotes();
  void read_quotes();
  void update_avg(build_state_t &);
  void upsert(candle_t &);
};
} // namespace DB

#endif
