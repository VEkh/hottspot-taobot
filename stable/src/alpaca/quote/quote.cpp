#ifndef ALPACA__QUOTE
#define ALPACA__QUOTE

#include "quote.h"                              // Alpaca::Quote
#include "alpaca/client/client.cpp"             // Alpaca::Client
#include "db/quote/quote.cpp"                   // DB::Quote
#include "db/streamed_quote/streamed_quote.cpp" // DB::StreamedQuote
#include "lib/pg/pg.cpp"                        // Pg
#include <map>                                  // std::map
#include <string>                               // std::string

#include "stream.cpp"
#include "watch.cpp"

Alpaca::Quote::Quote(Pg p, std::map<std::string, std::string> flags) {
  this->api_client = Alpaca::Client(flags);
  this->pg = p;
  this->db_quote = DB::Quote(this->pg);
  this->db_streamed_quote = DB::StreamedQuote(this->pg);
}

Alpaca::Quote::Quote(std::map<std::string, std::string> flags) {
  this->api_client = Alpaca::Client(flags);
}

#endif
