#ifndef OANDA__QUOTE
#define OANDA__QUOTE

#include "quote.h"                                 // Oanda::Quote
#include "db/margin_rate/margin_rate.cpp"          // DB::MarginRate
#include "db/quote/quote.cpp"                      // DB::Quote
#include "lib/market_availability/forex/forex.cpp" // MarketAvailability::Forex
#include "lib/pg/pg.cpp"                           // Pg
#include "oanda/client/client.cpp"                 // Oanda::Client
#include <map>                                     // std::map
#include <string>                                  // std::string

#include "watch.cpp"

Oanda::Quote::Quote(Pg p, std::map<std::string, std::string> flags) {
  this->api_client = Oanda::Client(flags);
  this->pg = p;

  this->db_quote = DB::Quote(this->pg);
  this->market_availability = MarketAvailability::Forex(this->pg);
}

Oanda::Quote::Quote(std::map<std::string, std::string> flags) {
  this->api_client = Oanda::Client(flags);
}

#endif
