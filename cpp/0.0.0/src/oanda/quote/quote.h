#ifndef OANDA__QUOTE_H
#define OANDA__QUOTE_H

#include "db/quote/quote.h"        // DB::Quote
#include "lib/formatted.cpp"       // Formatted
#include "lib/pg/pg.cpp"           // Pg
#include "oanda/client/client.cpp" // Oanda::Client
#include "oanda/types.cpp"         // Oanda::t
#include "types.cpp"               // Global::t
#include <list>                    // std::list
#include <map>                     // std::map
#include <string>                  // std::string

namespace Oanda {
class Quote {
public:
  using quote_t = Global::t::quote_t;

  Quote(){};
  Quote(Pg, std::map<std::string, std::string>);
  Quote(std::map<std::string, std::string>);

  void watch(const std::list<std::string> &);

private:
  constexpr static double AVG_ONE_SEC_VARIANCE_TIMEFRAME = 3.0 * 60.0;

  DB::Quote db_quote;
  Oanda::Client api_client;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg pg;
  std::map<std::string, quote_t> current_quotes;
  std::map<std::string, quote_t> previous_quotes;
  std::map<std::string, std::string> flags;

  quote_t fetch_quote(const std::string);
  quote_t get_quote(const std::string);

  void fetch_and_persist_quote(const std::string, const bool);
  void read(const std::string);
  void write();
};
} // namespace Oanda

#endif
