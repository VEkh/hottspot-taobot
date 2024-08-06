#ifndef DB__PRICE_ACTION_run
#define DB__PRICE_ACTION_run

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "log_day_candle.cpp"    // log_day_candle
#include "price_action.h"        // DB::PriceAction, duration, fmt
#include "process_quotes.cpp"    // process_quotes
#include "read_quotes.cpp"       // read_quotes
#include "update_avg.cpp"        // update_avg
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void DB::PriceAction::run() {
  std::cout << fmt.bold << fmt.underline << std::endl;
  std::cout << fmt.cyan << this->symbol;

  std::cout << fmt.bold << fmt.yellow;
  printf("'s Price Action\n");
  std::cout << std::endl << fmt.reset;

  read_quotes();
  process_quotes();
  update_avg();
  log_day_candle();

  std::cout << fmt.bold << fmt.cyan;
  printf("🎉 Completed in %s\n",
         ::utils::integer_::seconds_to_clock(duration()).c_str());
  std::cout << std::endl << fmt.reset;
}

#endif
