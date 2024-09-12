#ifndef DB__HISTORICAL_QUOTE__ALPACA_prepare_for_upsert
#define DB__HISTORICAL_QUOTE__ALPACA_prepare_for_upsert

#include "alpaca.h" // DB::HistoricalQuote::Alpaca, quote_t
#include "deps.cpp" // json
#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

DB::HistoricalQuote::Alpaca::quote_t
DB::HistoricalQuote::Alpaca::prepare_for_upsert(json &quote_json) {
  json wrapper;

  wrapper["quote"] = quote_json;

  quote_t quote = this->api_client.parse_quote(wrapper.dump());

  const std::string timestamp_string = quote_json["t"];
  const double raw_epoch = this->db_utils.timestamp_to_epoch(timestamp_string);

  const double half_second_rounded_epoch =
      floor(raw_epoch * 1000.0 / 500.0) * 500.0 / 1000.0;

  quote.symbol = this->symbol;
  quote.timestamp = half_second_rounded_epoch;

  if (this->debug) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Upserting ");
    std::cout << fmt.cyan << this->symbol;
    std::cout << fmt.yellow;
    printf(" quote of ");
    std::cout << fmt.green;
    printf("%'.2f", quote.mid());
    std::cout << fmt.yellow;
    printf(" at ");
    std::cout << fmt.magenta;
    printf("%s (%f rounded)", timestamp_string.c_str(),
           half_second_rounded_epoch);
    std::cout << fmt.reset << std::endl;
  }

  return quote;
}

#endif
