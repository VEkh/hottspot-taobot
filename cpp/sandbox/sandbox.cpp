#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"          // Pg
#include "models/quote/quote.cpp" // DB::Quote
#include <libpq-fe.h>             // PGconn, PQescapeLiteral, PQfreemem
#include <map>                    // std::map
#include <string>                 // std::string
#include <vector>                 // std::vector

int main() {
  Pg pg((std::map<std::string, std::string>){
      {"env", "development"},
  });

  pg.connect();

  DB::Quote db_quote(pg);

  db_quote.get("AMZN");

  db_quote.upsert({
      .ask = 99.0,
      .bid = 101.50,
      .price = 0.00,
      .symbol = "TSLA",
      .timestamp = 1678721705.176510,
  });

  db_quote.upsert({
      {
          .ask = 99.0,
          .bid = 101.50,
          .price = 0.00,
          .symbol = "AMZN",
          .timestamp = 1678482001.916087,
      },
      {
          .ask = 99.0,
          .bid = 101.50,
          .price = 0.00,
          .symbol = "TSLA",
          .timestamp = 1678482001.916087,
      },
  });

  pg.disconnect();
}
