#ifndef DB__HISTORICAL_QUOTE__BASE_download
#define DB__HISTORICAL_QUOTE__BASE_download

#include "base.h"                   // DB::HistoricalQuote::Base, quote_t
#include "deps.cpp"                 // json
#include "lib/utils/integer.cpp"    // ::utils::integer_
#include "print_download_intro.cpp" // print_download_intro
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf
#include <string>                   // std::string
#include <time.h>                   // time

void DB::HistoricalQuote::Base::download() {
  const long int clock_start = time(nullptr);
  int quotes_n = 0;

  while (this->start_at < this->end_at) {
    print_download_intro();

    json quotes_json = fetch_historical_quotes();

    if (quotes_json.empty()) {
      continue;
    }

    std::list<quote_t> quotes;

    for (json quote_json : quotes_json) {
      const quote_t quote = prepare_for_upsert(quote_json);

      if (quotes.empty() || quote.timestamp != this->start_at) {
        quotes.push_back(quote);
      }

      this->start_at = quote.timestamp;
    }

    this->db_quote.upsert(quotes);

    if (quotes.size() < 10) {
      this->start_at = this->end_at;
    }

    quotes_n += quotes.size();
  }

  const long int duration = time(nullptr) - clock_start;

  std::cout << fmt.bold << fmt.green;
  printf("🎉 Successfully downloaded %'i historical quotes(s) in %s\n", quotes_n,
         ::utils::integer_::seconds_to_clock(duration).c_str());
  std::cout << fmt.reset;
}

#endif
