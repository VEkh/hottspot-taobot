#ifndef DB__MARKET_SESSION_H
#define DB__MARKET_SESSION_H

#include "db/utils/utils.h" // DB::Utils
#include "lib/pg/pg.h"      // Pg
#include <list>             // std::list
#include <string>           // std::string

namespace DB {
class MarketSession {
public:
  struct find_or_create_by_args_t {
    double closed_at;
    bool debug = false;
    double opened_at;
    std::string symbol;
    double warm_up_period_seconds;
  };

  struct market_session_t {
    double close;
    double closed_at;
    double high;
    int id;
    double low;
    double open;
    double opened_at;
    std::string symbol;
    double warm_up_close;
    double warm_up_closed_at;
    double warm_up_high;
    double warm_up_low;
    double warm_up_open;
    double warm_up_opened_at;
  };

  MarketSession(){};
  MarketSession(Pg);

  market_session_t find_or_create_by(const find_or_create_by_args_t);
  void upsert(const market_session_t, const bool);

private:
  using query_result_t = Pg::query_result_t;

  DB::Utils db_utils;
  Pg conn;

  std::list<market_session_t> result_to_market_sessions(const query_result_t &);
};
}; // namespace DB

#endif
