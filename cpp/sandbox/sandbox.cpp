#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp" // Pg

int main() {
  Pg pg;
  pg.connect();
  pg.disconnect();

  // PQfinish(conn);
}
