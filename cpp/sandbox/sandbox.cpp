#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "db/quote/quote.cpp" // DB::Quote
#include "lib/pg/pg.cpp"      // Pg

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::Quote db_quote(pg);

  pg.disconnect();
}
