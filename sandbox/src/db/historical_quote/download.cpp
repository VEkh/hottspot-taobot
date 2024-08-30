#ifndef DB__HISTORICAL_QUOTE_download
#define DB__HISTORICAL_QUOTE_download

#include "deps.cpp"                 // nlohmann, json
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

    json quotes_json;

    try {
      quotes_json = json::parse(quotes_resp)["quotes"][this->symbol];
    } catch (nlohmann::json_abi_v3_11_2::detail::parse_error &) {
      std::cout << fmt.bold << fmt.red;
      printf("❌ Error parsing json:\n\n%s\n\nRetrying.", quotes_resp.c_str());
      std::cout << fmt.reset << std::endl;

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

    if (quotes.size() == 1) {
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
