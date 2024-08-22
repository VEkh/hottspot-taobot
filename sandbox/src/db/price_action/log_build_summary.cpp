#ifndef DB__PRICE_ACTION_log_build_summary
#define DB__PRICE_ACTION_log_build_summary

#include "lib/utils/integer.cpp" // ::utils::integer_
#include "price_action.h"        // DB::PriceAction, build_state_t
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void DB::PriceAction::log_build_summary(build_state_t &state) {
  std::cout << fmt.bold << fmt.yellow;
  printf("📅 Days Processed:     %i\n", state.days_n);

  printf("🤑 Avg Price Action:   ");
  std::cout << fmt.green;
  printf("%.2f%%\n", state.avg_price_action);

  std::cout << fmt.bold << fmt.yellow;
  printf("⌚ Time Running:       %s\n",
         ::utils::integer_::seconds_to_clock(state.duration()).c_str());

  std::cout << std::endl << fmt.reset;
}

#endif
