#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, snprintf
#include <string.h> // strlen
#include <string>   // std::string

#include "lib/pg/pg.cpp"          // Pg
#include "models/quote/quote.cpp" // DB::Quote
#include <libpq-fe.h>             // PGconn, PQescapeLiteral, PQfreemem

int main(int argc, char *argv[]) {
  const char *query = R"(
    select * from quotes where symbol = '%s'
  )";

  char formatted_query[strlen(query) + 1];

  snprintf(formatted_query, strlen(query) + 1, query, "TSLA");

  printf("Size of query: %i\n", (int)(strlen(query)));
  printf("%s\n", formatted_query);

  Pg pg;
  pg.connect();

  DB::Quote db_quote(pg);

  db_quote.get_last({
      .debug = true,
      .limit = 3,
      .symbol = "AMZN",
  });

  db_quote.get("AMZN", 10);

  pg.disconnect();
}
