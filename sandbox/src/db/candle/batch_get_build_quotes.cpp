#ifndef DB__CANDLE_batch_get_build_quotes
#define DB__CANDLE_batch_get_build_quotes

#include "candle.h"                       // DB::Candle, fmt, time_range_args_t
#include "get_build_quotes.cpp"           // get_build_quotes
#include "get_default_build_start_at.cpp" // get_default_build_start_at
#include "lib/utils/integer.cpp"          // ::utils::integer_
#include "lib/utils/time.cpp"             // ::utils::time_
#include <iostream>                       // std::cout, std::endl
#include <list>                           // std::list
#include <stdio.h>                        // printf
#include <time.h>                         // time

std::list<DB::Candle::quote_t>
DB::Candle::batch_get_build_quotes(const time_range_args_t args) {
  const double end_at = args.end_at ? args.end_at : time(nullptr);
  const double start_at =
      args.start_at ? args.start_at : get_default_build_start_at(args.debug);

  const double timer_start = time(nullptr);

  const std::string end_at_string =
      ::utils::time_::date_string(end_at, "%F %R CT", "America/Chicago");

  const std::string start_at_string =
      ::utils::time_::date_string(start_at, "%F %R CT", "America/Chicago");

  std::cout << fmt.bold << fmt.yellow;
  printf("💿 Reading Quotes from %s to %s...\n", start_at_string.c_str(),
         end_at_string.c_str());
  std::cout << std::endl << fmt.reset;

  const int batch_size = 1e6;
  double batch_start_at = start_at;
  int batch_n = 0;
  std::list<quote_t> batch;
  std::list<quote_t> build_quotes;

  while (true) {
    batch = get_build_quotes({
        .debug = args.debug,
        .end_at = end_at,
        .limit = batch_size,
        .start_at = batch_start_at,
    });

    for (const quote_t quote : batch) {
      build_quotes.push_back(quote);

      batch_start_at = quote.timestamp;
    }

    if (batch.size() <= 1) {
      break;
    }

    batch_n++;
    batch.clear();
    const double duration = time(nullptr) - timer_start;

    std::cout << fmt.bold << fmt.magenta;
    printf(
        "Batch %'i (Ends @ %s CT) => Quotes Read: %'i • Runtime: %s\n", batch_n,
        ::utils::time_::date_string(batch_start_at, "%F %R", "America/Chicago")
            .c_str(),
        (int)build_quotes.size(),
        ::utils::integer_::seconds_to_clock(duration).c_str());
    std::cout << fmt.reset;
  }

  const double duration = time(nullptr) - timer_start;

  std::cout << fmt.bold << fmt.cyan;
  printf("%'d", (int)build_quotes.size());

  std::cout << fmt.yellow;
  printf(" %s quotes loaded in %s\n", this->symbol.c_str(),
         ::utils::integer_::seconds_to_clock(duration).c_str());
  std::cout << std::endl << fmt.reset;

  return build_quotes;
};

#endif
