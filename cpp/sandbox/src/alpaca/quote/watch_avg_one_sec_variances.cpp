#ifndef ALPACA__QUOTE_watch_avg_one_sec_variances
#define ALPACA__QUOTE_watch_avg_one_sec_variances

#include "quote.h" // Alpaca::Quote
#include <list>    // std::list
#include <string>  // std::string

void Alpaca::Quote::watch_avg_one_sec_variances(
    const std::list<std::string> &symbols) {
  while (true) {
    this->db_quote.insert_latest_avg_one_sec_variances(symbols);
  }
}

#endif
