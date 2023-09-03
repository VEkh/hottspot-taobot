#ifndef DB__STREAMED_QUOTE_H
#define DB__STREAMED_QUOTE_H

#include "lib/pg/pg.cpp" // Pg
#include "types.cpp"     // Global::t
#include <string>        // std::string

namespace DB {
class StreamedQuote {
public:
  using quote_t = Global::t::quote_t;

  struct get_args_t {
    std::string symbol;
    bool debug = false;
  };

  struct upsert_args_t {
    double ask = 0.00;
    double bid = 0.00;
    std::string symbol;
    bool debug = false;
  };

  StreamedQuote(){};
  StreamedQuote(Pg c) : conn(c){};

  quote_t get(const get_args_t);
  void upsert(const upsert_args_t);

private:
  using query_result_t = Pg::query_result_t;

  Pg conn;

  quote_t result_to_quote(const query_result_t &);
};
} // namespace DB

#endif
