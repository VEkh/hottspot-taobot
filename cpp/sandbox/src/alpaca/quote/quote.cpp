#ifndef ALPACA__QUOTE
#define ALPACA__QUOTE

#include "quote.h"       // Alpaca::Quote
#include "lib/pg/pg.cpp" // Pg
#include <map>           // std::map
#include <string>        // std::string

#include "read_collection.cpp"
#include "read_price_movement.cpp"
#include "stream.cpp"
#include "watch.cpp"

Alpaca::Quote::Quote(Pg p) {
  this->pg = p;
  this->db_quote = DB::Quote(this->pg);
}

#endif
