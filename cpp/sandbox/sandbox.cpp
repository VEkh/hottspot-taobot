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

  std::vector<std::string> quotes = pg.query(R"(select * from quotes)");

  ::utils::debug::inspect(quotes);

  pg.disconnect();
}
