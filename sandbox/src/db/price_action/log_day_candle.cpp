#ifndef DB__PRICE_ACTION_log_day_candle
#define DB__PRICE_ACTION_log_day_candle

#include "lib/utils/time.cpp" // ::utils::time_
#include "price_action.h"     // DB::PriceAction, duration
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf
#include <time.h>             // time

void DB::PriceAction::log_day_candle() {
  std::cout << fmt.bold << fmt.magenta;
  printf("%s %s Candle\n",
         ::utils::time_::date_string(this->day_candle.opened_at, "%F",
                                     "America/Chicago")
             .c_str(),
         this->symbol.c_str());
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.cyan;
  printf("--------------------------------------\n");
  printf("Open:  %.2f • Opened At: %s\n", this->day_candle.open,
         ::utils::time_::date_string(this->day_candle.opened_at, "%R CT",
                                     "America/Chicago")
             .c_str());

  printf("Close: %.2f • Closed At: %s\n", this->day_candle.close,
         ::utils::time_::date_string(this->day_candle.closed_at, "%R CT",
                                     "America/Chicago")
             .c_str());

  printf("High:  %.2f • High At: %s\n", this->day_candle.high,
         ::utils::time_::date_string(this->day_candle.high_at, "%R CT",
                                     "America/Chicago")
             .c_str());

  printf("Low:   %.2f • Low At: %s\n", this->day_candle.low,
         ::utils::time_::date_string(this->day_candle.low_at, "%R CT",
                                     "America/Chicago")
             .c_str());
  printf("--------------------------------------\n");

  std::cout << fmt.bold << fmt.green;
  printf("💸 Price Action: %.2f%%\n", this->day_candle.range_open_percent());
  std::cout << std::endl << fmt.reset;

  std::cout << fmt.bold << fmt.yellow;
  printf("📅 Days Processed:     %i\n", this->days_n);

  printf("🤑 Avg Price Action:   ");
  std::cout << fmt.green;
  printf("%.2f%%\n", this->avg_price_action);

  std::cout << fmt.bold << fmt.yellow;
  printf("⌚ Time Running:       %s\n",
         ::utils::integer_::seconds_to_clock(duration()).c_str());

  std::cout << std::endl << fmt.reset;
}

#endif
