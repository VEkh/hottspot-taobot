#ifndef DB__STREAMED_QUOTE_H
#define DB__STREAMED_QUOTE_H

#include "lib/pg/pg.cpp" // Pg
#include <string>        // std::string

namespace DB {
class StreamedQuote {
public:
  struct upsert_args_t {
    double ask = 0.00;
    double bid = 0.00;
    std::string symbol;
    bool debug = false;
  };

  StreamedQuote(){};
  StreamedQuote(Pg c) : conn(c){};

  void upsert(const upsert_args_t);

private:
  Pg conn;
};
} // namespace DB

#endif
