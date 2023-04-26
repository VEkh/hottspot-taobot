#ifndef ALPACA__QUOTE_watch_avg_one_sec_variances
#define ALPACA__QUOTE_watch_avg_one_sec_variances

#include "quote.h" // Alpaca::Quote

void Alpaca::Quote::watch_avg_one_sec_variances() {
  while (true) {
    this->db_quote.insert_latest_avg_one_sec_variances();
  }
}

#endif
