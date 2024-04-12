#ifndef DB__HISTORICAL_QUOTE_print_download_intro
#define DB__HISTORICAL_QUOTE_print_download_intro

#include "historical_quote.h" // DB::HistoricalQuote, fmt
#include "lib/utils/time.cpp" // :utils::time_
#include <iostream>           // std::cout, std::endl
#include <list>               // std::list
#include <string>             // std::string

void DB::HistoricalQuote::print_download_intro() {
  std::cout << fmt.bold << fmt.yellow << std::endl;
  printf("Importing historical quotes for ");
  std::cout << fmt.cyan << this->symbol;
  std::cout << fmt.bold << fmt.yellow << " from ";
  std::cout << fmt.cyan
            << ::utils::time_::date_string(this->start_at, "%F %H:%M:%S CT",
                                           "America/Chicago");
  ;
  std::cout << fmt.bold << fmt.yellow << " to ";
  std::cout << fmt.cyan
            << ::utils::time_::date_string(this->end_at, "%F %H:%M:%S CT",
                                           "America/Chicago");
  std::cout << fmt.reset << std::endl << std::endl;
}

#endif
