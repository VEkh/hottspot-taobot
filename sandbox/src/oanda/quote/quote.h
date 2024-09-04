#ifndef OANDA__QUOTE_H
#define OANDA__QUOTE_H

#include "db/quote/quote.h"                              // DB::Quote
#include "lib/forex_availability/forex_availability.cpp" // ForexAvailability
#include "lib/formatted.cpp"                             // Formatted
#include "lib/pg/pg.cpp"                                 // Pg
#include "oanda/client/client.cpp"                       // Oanda::Client
#include "oanda/types.cpp"                               // Oanda::t
#include "types.cpp"                                     // Global::t
#include <list>                                          // std::list
#include <map>                                           // std::map
#include <string>                                        // std::string

namespace Oanda {
class Quote {
public:
  using quote_t = Global::t::quote_t;

  Quote(){};
  Quote(Pg, std::map<std::string, std::string>);
  Quote(std::map<std::string, std::string>);

  DB::Quote db_quote;

  void watch(const std::list<std::string> &);

private:
  ForexAvailability market_availability;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Oanda::Client api_client;
  Pg pg;
  std::map<std::string, quote_t> current_quotes;
  std::map<std::string, quote_t> previous_quotes;
  std::map<std::string, std::string> flags;

  quote_t fetch_quote(const std::string);
  quote_t get_quote(const std::string);

  void fetch_and_persist_quote(const std::string, const bool);
};
} // namespace Oanda

#endif
