#ifndef DB__QUOTE_watch_avg_one_sec_variances
#define DB__QUOTE_watch_avg_one_sec_variances

#include "insert_latest_avg_one_sec_variances.cpp" // insert_latest_avg_one_sec_variances
#include "quote.h"                                 // DB::Quote
#include <list>                                    // std::list
#include <string>                                  // std::string

void DB::Quote::watch_avg_one_sec_variances(
    const std::list<std::string> &symbols) {
  while (true) {
    insert_latest_avg_one_sec_variances(symbols);
  }
}

#endif
