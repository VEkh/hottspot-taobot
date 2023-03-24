#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"          // Pg
#include "models/quote/quote.cpp" // DB::Quote
#include <libpq-fe.h>             // PGconn, PQescapeLiteral, PQfreemem

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::Quote db_quote(pg);

  db_quote.get_last({
      .debug = true,
      .limit = 3,
      .symbol = "AMZN",
  });

  db_quote.get("AMZN", 10);

  db_quote.insert_latest_avg_one_sec_variances();

  pg.disconnect();
}
