#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"       // Pg
#include "lib/utils/debug.cpp" // ::utils::debug
#include <string>              // std::string
#include <vector>              // std::vector

int main() {
  Pg pg;
  pg.connect();

  std::vector<std::string> quotes = pg.exec(R"(
    insert into quotes(ask, bid, symbol, timestamp)
      values (99.0, 101.50, 'AMZN', '2023-03-08 23:06:46.000000+00');
  )");

  ::utils::debug::inspect(quotes);

  pg.disconnect();
}
