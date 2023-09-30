#ifndef DB__CANDLE_build
#define DB__CANDLE_build

#include "candle.h"              // DB::Candle, candle_t, fmt, quote_t
#include "db/quote/quote.cpp"    // DB::Quote
#include "get_latest_quotes.cpp" // get_latest_quotes
#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/time.cpp"    // ::utils::time_
#include "quote_to_bounds.cpp"   // quote_to_bounds
#include "upsert.cpp"            // upsert
#include <algorithm>             // std::max, std::min
#include <iostream>              // std::cout, std::endl
#include <iterator>              // std::next
#include <list>                  // std::list
#include <math.h>                // INFINITY
#include <stdio.h>               // printf
#include <time.h>                // time

void DB::Candle::build() {
  std::cout << fmt.bold << fmt.cyan;
  std::cout << "🔥 Building " << this->duration_minutes
            << " Minute Candles for ";
  std::cout << fmt.yellow << this->symbol << std::endl;
  std::cout << fmt.reset << std::endl;

  const long int clock_start = time(nullptr);

  const std::list<quote_t> latest_quotes = get_latest_quotes();

  candle_t candle;
  int candles_count = 0;
  int quotes_count = 1;
  std::list<quote_t>::const_iterator quote = latest_quotes.begin();

  std::cout << fmt.bold << fmt.cyan;
  printf("💲 %i quotes loaded\n", (int)latest_quotes.size());
  std::cout << fmt.reset << std::endl;

  for (; quote != latest_quotes.end(); quote++, quotes_count++) {
    const candle_bounds_t bounds = quote_to_bounds(*quote);
    const double mid = quote->mid();

    if (candle.closed_at && (quote->timestamp > candle.closed_at ||
                             std::next(quote) == latest_quotes.end())) {
      upsert(candle);
      candle = candle_t();
      candles_count++;
    }

    candle.close = mid;
    candle.closed_at = bounds.closed_at;
    candle.high = std::max(candle.high, mid);
    candle.low = std::min(candle.low, mid);
    candle.open = candle.open ? candle.open : mid;
    candle.opened_at = bounds.opened_at;
    candle.symbol = quote->symbol;

    if (quotes_count % 1000 == 0) {
      std::cout << fmt.bold << fmt.yellow << fmt.underline;
      std::cout << "📝 " << this->symbol;
      printf(" %i Min Candle Build Report\n", this->duration_minutes);

      std::cout << fmt.no_underline << fmt.cyan;
      printf("Candles Upserted: %i\n", candles_count);
      printf("Latest Opened At: %s\n",
             ::utils::time_::date_string(
                 candle.opened_at, "%a, %b %d, %Y %X %Z", "America/Chicago")
                 .c_str());
      printf("Quotes Processed: %i\n", quotes_count);
      std::cout << fmt.reset << std::endl;
    }
  }

  const long int duration = time(nullptr) - clock_start;

  std::cout << fmt.bold << fmt.green;
  printf("🎉 Successfully built %i candle(s) in %s\n", candles_count,
         ::utils::integer_::seconds_to_clock(duration).c_str());
  std::cout << fmt.reset;
}

#endif
