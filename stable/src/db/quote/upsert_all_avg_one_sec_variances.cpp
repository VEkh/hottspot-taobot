#ifndef DB__QUOTE_upsert_all_avg_one_sec_variances
#define DB__QUOTE_upsert_all_avg_one_sec_variances

#include "get_last.cpp"                    // get_last
#include "lib/formatted.cpp"               // Formatted
#include "quote.h"                         // DB::Quote, quote_t
#include "upsert_avg_one_sec_variance.cpp" // upsert_avg_one_sec_variance
#include <iostream>                        // std::cout, std::endl
#include <string>                          // std::string
#include <time.h>                          // time
#include <vector>                          // std::vector

void DB::Quote::upsert_all_avg_one_sec_variances(
    const upsert_all_avg_one_sec_variances_args_t args) {
  const Formatted::fmt_stream_t fmt = Formatted::stream();

  const bool debug = args.debug;
  const std::string symbol = args.symbol;
  const std::string starting_from = args.starting_from;

  double timestamp_upper_bound =
      starting_from.empty() ? time(nullptr) : std::stod(starting_from);

  std::vector<quote_t> quotes = get_last({
      .limit = 1,
      .limit_offset = 0,
      .symbol = symbol,
      .timestamp_upper_bound = timestamp_upper_bound,
      .debug = debug,
  });

  while (quotes.size()) {
    for (const quote_t quote : quotes) {
      upsert_avg_one_sec_variance({
          .id = quote.id,
          .symbol = symbol,
          .debug = debug,
      });

      if (!debug) {
        std::cout << fmt.bold << fmt.yellow;
        printf("✅ Successfully upserted ");
        std::cout << fmt.no_bold << fmt.cyan << symbol;
        std::cout << fmt.bold << fmt.yellow;

        std::cout << " quote " << fmt.red << quote.id;
        std::cout << fmt.yellow;
        printf("'s (@ %f) average one second variance.\n", quote.timestamp);
        std::cout << fmt.reset << std::endl;
      }

      timestamp_upper_bound = quote.timestamp;
    }

    quotes = get_last({
        .limit = 1,
        .limit_offset = 1,
        .symbol = symbol,
        .timestamp_upper_bound = timestamp_upper_bound,
        .debug = debug,
    });
  }
}

#endif
