#ifndef DB__FIVE_MIN_CANDLES_H
#define DB__FIVE_MIN_CANDLES_H

#include "db/quote/quote.cpp" // DB::Quote
#include "lib/formatted.cpp"  // Formatted
#include "lib/pg/pg.cpp"      // Pg
#include "types.cpp"          // Global::t
#include <string>             // std::string
#include <vector>             // std::vector

namespace DB {
class FiveMinCandles {
public:
  FiveMinCandles(const Pg, const std::string);

  void build();

private:
  using query_result_t = Pg::query_result_t;
  using quote_t = Global::t::quote_t;

  DB::Quote db_quote;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg conn;
  std::string symbol;

  std::vector<quote_t> get_latest_quotes(const bool);
};
} // namespace DB

#endif
