#ifndef DB__PRICE_ACTION_build
#define DB__PRICE_ACTION_build

#include "init_build_state.cpp"  // init_build_state
#include "lib/utils/integer.cpp" // ::utils::integer_
#include "price_action.h"        // DB::PriceAction, build_args_t, fmt
#include "process_quotes.cpp"    // process_quotes
#include "read_quotes.cpp"       // read_quotes
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void DB::PriceAction::build(const build_args_t args) {
  std::cout << fmt.bold << fmt.underline << std::endl;
  std::cout << fmt.cyan << this->symbol;

  std::cout << fmt.bold << fmt.yellow;
  printf("'s Price Action\n");
  std::cout << std::endl << fmt.reset;

  init_build_state(args);
  read_quotes();
  process_quotes();

  std::cout << fmt.bold << fmt.cyan;
  printf("🎉 Completed in %s\n",
         ::utils::integer_::seconds_to_clock(this->build_state.duration())
             .c_str());
  std::cout << std::endl << fmt.reset;
}

#endif
