#ifndef DB__PRICE_ACTION_read_quotes
#define DB__PRICE_ACTION_read_quotes

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/time.cpp"    // ::utils::time_
#include "price_action.h"        // DB::PriceAction, fmt, quote_t
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf
#include <time.h>                // time

void DB::PriceAction::read_quotes() {
  const std::string end_at_string = ::utils::time_::date_string(
      this->build_state.end_at, "%F %R CT", "America/Chicago");

  const std::string start_at_string = ::utils::time_::date_string(
      this->build_state.start_at, "%F %R CT", "America/Chicago");

  std::cout << fmt.bold << fmt.yellow;
  printf("💿 Reading Quotes from %s to %s...\n", start_at_string.c_str(),
         end_at_string.c_str());
  std::cout << std::endl << fmt.reset;

  const int batch_size = 1e6;
  double batch_start_at = this->build_state.start_at;
  int batch_n = 0;
  std::list<quote_t> batch;

  while (true) {
    batch = this->db_quote.get_last({
        .debug = this->debug,
        .end_at = this->build_state.end_at,
        .limit = batch_size,
        .sort_direction = "asc",
        .start_at = batch_start_at,
        .symbol = this->symbol,
    });

    for (const quote_t quote : batch) {
      this->build_state.quotes.push_back(quote);

      batch_start_at = quote.timestamp;
    }

    if (batch.size() <= 1) {
      break;
    }

    batch_n++;
    batch.clear();
    const double quotes_get_seconds = this->build_state.duration();

    std::cout << fmt.bold << fmt.magenta;
    printf(
        "Batch %'i (Ends @ %s CT) => Quotes Read: %'i • Runtime: %s\n", batch_n,
        ::utils::time_::date_string(batch_start_at, "%F %R", "America/Chicago")
            .c_str(),
        (int)this->build_state.quotes.size(),
        ::utils::integer_::seconds_to_clock(quotes_get_seconds).c_str());
    std::cout << fmt.reset;
  }

  const double quotes_get_seconds = this->build_state.duration();

  std::cout << fmt.bold << fmt.cyan;
  printf("%'d", (int)this->build_state.quotes.size());

  std::cout << fmt.yellow;
  printf(" %s quotes loaded in %s\n", this->symbol.c_str(),
         ::utils::integer_::seconds_to_clock(quotes_get_seconds).c_str());
  std::cout << std::endl << fmt.reset;
}

#endif
