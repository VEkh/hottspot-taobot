#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT_log_duration
#define PERFORMANCE__ACCOUNT_SNAPSHOT_log_duration

#include "account_snapshot.h"    // Performance::AccountSnapshot, fmt
#include "lib/utils/integer.cpp" // ::utils::integer_
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf
#include <time.h>                // time

void Performance::AccountSnapshot::log_duration() {
  const double duration = time(nullptr) - this->timer_start;

  std::cout << fmt.bold << fmt.cyan;
  printf("⌚ Finished in %s\n",
         ::utils::integer_::seconds_to_clock(duration).c_str());
  std::cout << fmt.reset << std::endl;
}

#endif
