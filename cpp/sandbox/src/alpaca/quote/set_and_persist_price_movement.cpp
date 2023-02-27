#ifndef ALPACA__QUOTE_set_and_persist_price_movement
#define ALPACA__QUOTE_set_and_persist_price_movement

#include "quote.h"                  // Alpaca::Quote
#include "set_price_movement.cpp"   // set_price_movement
#include "write_price_movement.cpp" // write_price_movement
#include <string>                   // std::string

void Alpaca::Quote::set_and_persist_price_movement(const std::string symbol) {
  set_price_movement(symbol);
  write_price_movement(symbol);
}

#endif
