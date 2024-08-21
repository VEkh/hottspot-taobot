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
  struct init_args_t {
    Pg conn;
    bool debug = false;
    std::string end_at;
    std::string start_at;
    std::string symbol;
  };

  PriceAction(const init_args_t);
  PriceAction(){};

  void run();

private:
  using candle_t = Global::t::candle_t;
  using quote_t = Global::t::quote_t;

  DB::Quote db_quote;
  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  NyseAvailability market_availability;
  Pg conn;

  bool debug;

  candle_t day_candle;

  double avg_price_action = 0.0;
  double end_at;
  double price_action_sum = 0.0;
  double start_at;
  double timer_start;

  int days_n = 0;

  std::list<quote_t> quotes;
  std::string symbol;

  int duration() { return time(nullptr) - this->timer_start; };

  void log_day_candle();
  void process_quotes();
  void read_quotes();
  void update_avg();
  void upsert();
};
} // namespace DB

#endif
