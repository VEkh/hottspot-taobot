#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"                        // Pg
#include "lib/utils/time.cpp"                   // ::utils::time_
#include "models/account_stat/account_stat.cpp" // DB::AccountStat
#include <libpq-fe.h> // PGconn, PQescapeLiteral, PQfreemem
#include <string.h>   // strlen

int main(int argc, char *argv[]) {
  const double day_start = ::utils::time_::beginning_of_day_to_epoch();

  Pg pg;
  pg.connect();

  DB::AccountStat db_account_stat(pg);

  db_account_stat.get_snapshot({
      .api_key_id = "PKB5FJN28HVP0TNZV00B",
      .session_started_at = day_start,
      .starting_from = day_start,
      .debug = true,
  });

  pg.disconnect();
}
