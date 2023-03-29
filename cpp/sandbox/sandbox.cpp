#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"          // Pg
#include "models/quote/quote.cpp" // DB::Quote
#include <libpq-fe.h>             // PGconn, PQescapeLiteral, PQfreemem
#include <string.h>               // strlen

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::Quote db_quote(pg);

  DB::Quote::one_sec_variance_avgs_t averages =
      db_quote.get_one_sec_variance_avgs("AMZN");

  printf("latest: %.5f • running: %.5f\n", averages.latest, averages.running);

  pg.disconnect();
}
