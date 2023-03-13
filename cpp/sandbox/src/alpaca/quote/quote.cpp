#ifndef ALPACA__QUOTE
#define ALPACA__QUOTE

#include "quote.h"        // Alpaca::Quote
#include "initialize.cpp" // initialize
#include <map>            // std::map
#include <string>         // std::string

#include "read_collection.cpp"
#include "read_price_movement.cpp"
#include "stream.cpp"
#include "watch.cpp"

Alpaca::Quote::Quote(std::map<std::string, std::string> f = {}) {
  initialize(f);
}

#endif
