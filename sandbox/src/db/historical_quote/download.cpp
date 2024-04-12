#ifndef DB__HISTORICAL_QUOTE_download
#define DB__HISTORICAL_QUOTE_download

#include "deps.cpp"                 // json
#include "historical_quote.h"       // DB::HistoricalQuote, quote_t
#include "prepare_for_upsert.cpp"   // prepare_for_upsert
#include "print_download_intro.cpp" // print_download_intro
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf
#include <string>                   // std::string
#include <time.h>                   // time

void DB::HistoricalQuote::download() {
  const long int clock_start = time(nullptr);
  int quotes_n = 0;

  while (this->start_at < this->end_at) {
    print_download_intro();

    std::string quotes_resp = this->api_client.fetch_historical_quotes({
        .batch = this->batch,
        .end_at = this->end_at,
        .start_at = this->start_at,
        .symbol = this->symbol,
    });

    json quotes_json = json::parse(quotes_resp)["quotes"][this->symbol];

    for (json quote_json : quotes_json) {
      const quote_t quote = prepare_for_upsert(quote_json);

      this->start_at = quote.timestamp;
      this->db_quote.upsert(quote);

      if (quotes_json.size() == 1) {
        this->start_at = this->end_at;
      }

      quotes_n++;
    }
  }

  const long int duration = time(nullptr) - clock_start;

  std::cout << fmt.bold << fmt.green;
  printf("🎉 Successfully downloaded %i historical quotes(s) in %s\n", quotes_n,
         ::utils::integer_::seconds_to_clock(duration).c_str());
  std::cout << fmt.reset;
}

#endif
