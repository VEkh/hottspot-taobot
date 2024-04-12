#ifndef DB__HISTORICAL_QUOTE_H
#define DB__HISTORICAL_QUOTE_H

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "db/quote/quote.cpp"       // DB::Quote
#include "db/utils/utils.cpp"       // DB::Utils
#include "deps.cpp"                 // json
#include "lib/formatted.cpp"        // Formatted
#include "lib/pg/pg.h"              // Pg
#include "types.cpp"                // Global::t
#include <string>                   // std::string
#include <time.h>                   // time

namespace DB {
class HistoricalQuote {
public:
  using quote_t = Global::t::quote_t;

  struct init_args_t {
    std::string batch = "10000";
    Pg conn;
    bool debug = false;
    std::string end_at;
    std::string start_at;
    std::string symbol;
  };

  HistoricalQuote(){};
  HistoricalQuote(const init_args_t);

  void download();

private:
  Alpaca::Client api_client;
  DB::Quote db_quote;
  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;

  bool debug;
  int batch;
  double end_at = time(nullptr);
  double start_at = time(nullptr);
  std::string symbol;

  quote_t prepare_for_upsert(json &);

  void print_download_intro();
};
} // namespace DB

#endif
