#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"          // Pg
#include "models/utils/utils.cpp" // DB::Utils

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::Utils db_utils(pg);

  db_utils.set_param({"statement_timeout", "1000"}, true);

  pg.disconnect();
}
