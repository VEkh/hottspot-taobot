#ifndef DB__HISTORICAL_QUOTE__OANDA_prepare_for_upsert
#define DB__HISTORICAL_QUOTE__OANDA_prepare_for_upsert

#include "deps.cpp"           // json
#include "lib/utils/time.cpp" // ::utils::time_
#include "oanda.h"            // DB::HistoricalQuote::Oanda, quote_t
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf

DB::HistoricalQuote::Oanda::quote_t
DB::HistoricalQuote::Oanda::prepare_for_upsert(json &quote_json) {
  quote_t quote = {
      .ask = quote_json["ask"],
      .bid = quote_json["bid"],
      .symbol = this->symbol,
      .timestamp = quote_json["time"],
  };

  if (this->debug) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Upserting ");
    std::cout << fmt.cyan << this->symbol;
    std::cout << fmt.yellow;
    printf(" quote of ");
    std::cout << fmt.green;
    printf("%'.5f", quote.mid());
    std::cout << fmt.yellow;
    printf(" at ");
    std::cout << fmt.magenta;
    printf("%s", ::utils::time_::date_string(quote.timestamp, "%F %T CT",
                                             "America/Chicago")
                     .c_str());
    std::cout << fmt.reset << std::endl;
  }

  return quote;
}

#endif
