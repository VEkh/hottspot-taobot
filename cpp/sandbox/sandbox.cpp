#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"                        // Pg
#include "models/account_stat/account_stat.cpp" // DB::AccountStat
#include <libpq-fe.h> // PGconn, PQescapeLiteral, PQfreemem
#include <string.h>   // strlen

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::AccountStat db_account_stat(pg);

  db_account_stat.insert({
      .api_key_id = "api_key_dev",
      .equity = 3e4,
      .margin_buying_power = 3e4 * 4,
      .margin_multiplier = 4,
  });

  pg.disconnect();
}
