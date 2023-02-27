#ifndef ALPACA__QUOTE_current_price
#define ALPACA__QUOTE_current_price

#include "quote.h" // Alpaca::Quote
#include <string>  // std::string

double Alpaca::Quote::current_price(const std::string symbol) {
  return this->quotes[symbol].back().price;
}

#endif
