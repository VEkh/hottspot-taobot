#ifndef DB__PRICE_ACTION_log_candle
#define DB__PRICE_ACTION_log_candle

#include "lib/utils/time.cpp" // ::utils::time_
#include "price_action.h"     // DB::PriceAction, duration
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf
#include <time.h>             // time

void DB::PriceAction::log_candle(candle_t &candle) {
  std::cout << fmt.bold << fmt.magenta;
  printf("%s %s Candle\n",
         ::utils::time_::date_string(candle.opened_at, "%F", "America/Chicago")
             .c_str(),
         this->symbol.c_str());
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.cyan;
  printf("--------------------------------------\n");
  printf(
      "Open:  %.2f • Opened At: %s\n", candle.open,
      ::utils::time_::date_string(candle.opened_at, "%R CT", "America/Chicago")
          .c_str());

  printf(
      "Close: %.2f • Closed At: %s\n", candle.close,
      ::utils::time_::date_string(candle.closed_at, "%R CT", "America/Chicago")
          .c_str());

  printf("High:  %.2f • High At: %s\n", candle.high,
         ::utils::time_::date_string(candle.high_at, "%R CT", "America/Chicago")
             .c_str());

  printf("Low:   %.2f • Low At: %s\n", candle.low,
         ::utils::time_::date_string(candle.low_at, "%R CT", "America/Chicago")
             .c_str());
  printf("--------------------------------------\n");

  std::cout << fmt.bold << fmt.green;
  printf("💸 Price Action: %.2f%%\n", candle.range_open_percent());
  std::cout << std::endl << fmt.reset;
}

#endif
