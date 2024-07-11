#ifndef DB__MARKET_CLOSE_H
#define DB__MARKET_CLOSE_H

#include "lib/pg/pg.cpp" // Pg
#include <list>          // std::list
#include <string>        // std::string

namespace DB {
class MarketClose {
public:
  using query_result_t = Pg::query_result_t;

  MarketClose(){};
  MarketClose(const Pg c) : conn(c){};

  struct get_symbols_closed_at_args_t {
    std::string api_key_id;
    bool debug = false;
    double epoch = 0;
  };

  struct market_close_t {
    std::string api_key_id;
    double closed_at;
    std::string symbol;
  };

  struct upsert_args_t {
    std::string api_key_id;
    double closed_at = 0;
    bool debug = false;
    std::string symbol;
  };

  std::list<std::string>
  get_symbols_closed_at(const get_symbols_closed_at_args_t);

  void upsert(const upsert_args_t);

private:
  Pg conn;

  std::list<market_close_t> result_to_market_closes(const query_result_t &);
};
} // namespace DB

#endif
