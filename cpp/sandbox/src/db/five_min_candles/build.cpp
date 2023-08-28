#ifndef DB__FIVE_MIN_CANDLES_build
#define DB__FIVE_MIN_CANDLES_build

#include "db/quote/quote.cpp"    // DB::Quote
#include "five_min_candles.h"    // DB::FiveMinCandles, candle_t, fmt, quote_t
#include "get_latest_quotes.cpp" // get_latest_quotes
#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/time.cpp"    // ::utils::time_
#include "upsert.cpp"            // upsert
#include <algorithm>             // std::max, std::min
#include <iostream>              // std::cout, std::endl
#include <list>                  // std::list
#include <math.h>                // INFINITY
#include <stdio.h>               // printf
#include <time.h>                // time

void DB::FiveMinCandles::build() {
  std::cout << fmt.bold << fmt.cyan;
  std::cout << "🔥 Building 5 Minute Candles for ";
  std::cout << fmt.yellow << this->symbol << std::endl;
  std::cout << fmt.reset << std::endl;

  const long int clock_start = time(nullptr);

  const std::list<quote_t> latest_quotes = get_latest_quotes();

  candle_t candle;
  int candles_count = 0;
  int quotes_count = 1;
  std::list<quote_t>::const_iterator quote = latest_quotes.begin();

  for (; quote != latest_quotes.end(); quote++, quotes_count++) {
    const double mid = quote->mid();
    candle.high = std::max(candle.high, mid);
    candle.low = std::min(candle.low, mid);
    candle.open = candle.open ? candle.open : mid;
    candle.opened_at = candle.opened_at ? candle.opened_at : quote->timestamp;
    candle.symbol = quote->symbol;

    if (quotes_count % 1000 == 0) {
      std::cout << fmt.bold << fmt.yellow << fmt.underline;
      std::cout << "📝 " << this->symbol;
      printf(" 5 Min Candle Build Report\n");

      std::cout << fmt.no_underline << fmt.cyan;
      printf("Candles Upserted: %i\n", candles_count);
      printf("Latest Opened At: %s\n",
             ::utils::time_::date_string(
                 candle.opened_at, "%a, %b %d, %Y %X %Z", "America/Chicago")
                 .c_str());
      printf("Quotes Processed: %i\n", quotes_count);
      std::cout << fmt.reset << std::endl;
    }

    if (quote->id == latest_quotes.back().id ||
        (quote->timestamp - candle.opened_at) >= CANDLE_DURATION_SECONDS) {
      candle.close = mid;
      candle.closed_at = quote->timestamp;
      upsert(candle);
      candle = candle_t();
      candles_count++;
    }
  }

  const long int duration = time(nullptr) - clock_start;

  std::cout << fmt.bold << fmt.green;
  printf("🎉 Successfully built candles in %s\n",
         ::utils::integer_::seconds_to_clock(duration).c_str());
  std::cout << fmt.reset;
}

#endif
