#ifndef DB__HISTORICAL_QUOTE__BASE_H
#define DB__HISTORICAL_QUOTE__BASE_H

#include "db/quote/quote.cpp" // DB::Quote
#include "db/utils/utils.cpp" // DB::Utils
#include "deps.cpp"           // json
#include "lib/formatted.cpp"  // Formatted
#include "lib/pg/pg.h"        // Pg
#include "types.cpp"          // Global::t
#include <string>             // std::string
#include <time.h>             // time

namespace DB {
namespace HistoricalQuote {
class Base {
public:
  using quote_t = Global::t::quote_t;

  struct init_args_t {
    std::string batch_size = "10000";
    Pg conn;
    bool debug = false;
    std::string end_at;
    std::string start_at;
    std::string symbol;
  };

  Base(){};
  Base(const init_args_t);

  void download();

protected:
  DB::Quote db_quote;
  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;

  bool debug;
  int batch_size;
  double end_at = time(nullptr);
  double start_at = time(nullptr);
  std::string symbol;

  virtual json fetch_historical_quotes() { return R"({})"_json; };

  virtual quote_t prepare_for_upsert(json &) { return quote_t(); };

  void print_download_intro();
};
} // namespace HistoricalQuote
} // namespace DB

#endif
