#ifndef DB__CANDLE_print_build_intro
#define DB__CANDLE_print_build_intro

#include "candle.h"           // DB::Candle, fmt, time_range_args_t
#include "lib/utils/time.cpp" // ::utils::time_
#include <iostream>           // std::cout, std::endl

void DB::Candle::print_build_intro(const time_range_args_t args) {
  const double end_at = args.end_at;
  const double start_at = args.start_at;

  std::cout << fmt.bold << fmt.yellow;
  std::cout << "🔥 Building " << this->duration_minutes
            << " Minute Candles for ";
  std::cout << fmt.cyan << this->symbol;

  if (start_at) {
    std::cout << fmt.bold << fmt.yellow;
    std::cout << " from ";
    std::cout << fmt.cyan;
    std::cout << ::utils::time_::date_string(start_at, "%F %H:%M:%S CT",
                                             "America/Chicago");
  }

  if (end_at) {
    std::cout << fmt.bold << fmt.yellow;
    std::cout << " to ";
    std::cout << fmt.cyan;
    std::cout << ::utils::time_::date_string(end_at, "%F %H:%M:%S CT",
                                             "America/Chicago");
  }

  std::cout << fmt.reset << std::endl << std::endl;
}

#endif
