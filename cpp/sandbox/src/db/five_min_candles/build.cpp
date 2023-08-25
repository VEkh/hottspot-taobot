#ifndef DB__FIVE_MIN_CANDLES_build
#define DB__FIVE_MIN_CANDLES_build

#include "five_min_candles.h"    // DB::FiveMinCandles, fmt, quote_t
#include "get_latest_quotes.cpp" // get_latest_quotes
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf
#include <vector>                // std::vector

void DB::FiveMinCandles::build() {
  std::cout << fmt.bold << fmt.cyan;
  std::cout << "🔥 Building five minute candles for ";
  std::cout << fmt.yellow << this->symbol << std::endl;
  std::cout << fmt.reset;

  // Get most recent candle's opened_at
  // Get all quotes since that time
  const std::vector<quote_t> latest_quotes = get_latest_quotes(true);
  printf("Loading %i quotes for %s\n", (int)latest_quotes.size(),
         this->symbol.c_str());

  // Iterate through quotes
  // Each time a candle is built, upsert insert it into the database
}

#endif
