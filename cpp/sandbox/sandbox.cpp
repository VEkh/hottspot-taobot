#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"          // Pg
#include "models/quote/quote.cpp" // DB::Quote
#include <libpq-fe.h>             // PGconn, PQescapeLiteral, PQfreemem
#include <map>                    // std::map
#include <string>                 // std::string
#include <vector>                 // std::vector

#include "lib/utils/time.cpp" // ::utils::time_

int main() {
  printf("Epoch: %.10f\n", ::utils::time_::quote_timestamp_to_epoch_double(
                               "2023-03-14T14:38:00.195355826Z"));

  const double now = ::utils::time_::epoch("nanoseconds") / 1.0e9;

  printf("%.9f\n", now);

  std::map<std::string, std::string> flags = {
      {"env", "development"},
  };

  Pg pg(flags);
  pg.connect();

  DB::Quote db_quote(pg);

  db_quote.get("AMZN");

  pg.disconnect();
}
