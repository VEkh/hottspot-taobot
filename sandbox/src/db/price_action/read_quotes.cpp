#ifndef DB__PRICE_ACTION_read_quotes
#define DB__PRICE_ACTION_read_quotes

#include "price_action.h" // DB::PriceAction, fmt, quote_t
#include <iostream>       // std::cout, std::endl
#include <stdio.h>        // printf
#include <time.h>         // time

void DB::PriceAction::read_quotes() {
  std::cout << fmt.bold << fmt.yellow;
  printf("💿 Reading Quotes...\n");
  std::cout << std::endl << fmt.reset;

  this->quotes = this->db_quote.get_last({
      .debug = this->debug,
      .end_at = this->end_at,
      .sort_direction = "asc",
      .start_at = this->start_at,
      .symbol = this->symbol,
  });

  const double quotes_get_seconds = time(nullptr) - this->timer_start;

  std::cout << fmt.bold << fmt.cyan;
  printf("%'d", (int)quotes.size());

  std::cout << fmt.yellow;
  printf(" %s quotes loaded in %s\n", this->symbol.c_str(),
         ::utils::integer_::seconds_to_clock(quotes_get_seconds).c_str());
  std::cout << std::endl << fmt.reset;
}

#endif
