#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"          // Pg
#include "models/quote/quote.cpp" // DB::Quote
#include <libpq-fe.h>             // PGconn, PQescapeLiteral, PQfreemem
#include <string>                 // std::string
#include <vector>                 // std::vector

int main() {
  Pg pg;
  pg.connect();

  DB::Quote db_quote(pg);

  db_quote.get("AMZN", 10);

  // std::vector<std::string> quotes = pg.exec(R"(
  //   select row_to_json(quotes) from quotes
  // )");

  // pg.exec(R"(
  //   insert into quotes(ask, bid, symbol, timestamp)
  //     values (99.0, 101.50, 'AMZN', '2023-03-10T21:00:01.91608747Z');
  // )");

  pg.disconnect();
}
