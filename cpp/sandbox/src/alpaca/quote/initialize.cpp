#ifndef ALPACA__QUOTE_initialize
#define ALPACA__QUOTE_initialize

#include "lib/pg/pg.cpp"          // Pg
#include "models/quote/quote.cpp" // DB::Quote
#include "quote.h"                // Alpaca::Quote
#include <map>                    // std::map
#include <string>                 // std::string

void Alpaca::Quote::initialize(std::map<std::string, std::string> flags_ = {}) {
  this->flags = flags_;

  this->pg = Pg(this->flags);
  this->pg.connect();

  this->db_quote = DB::Quote(this->pg);
}

#endif
