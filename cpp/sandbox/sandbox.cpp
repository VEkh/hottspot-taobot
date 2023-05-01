#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "db/margin_rate/margin_rate.cpp" // DB::MarginRate
#include "lib/pg/pg.cpp"                  // Pg

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::MarginRate db_margin_rate(pg);

  db_margin_rate.insert({
      .multiplier = (100.0 / 3),
      .symbol = "eur_usd",
      .debug = true,
  });

  const DB::MarginRate::margin_rate_t margin_rate =
      db_margin_rate.get("EUR_USD");

  printf("multiplier: %f\n", margin_rate.multiplier);

  pg.disconnect();
}
