#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"                            // Pg
#include "models/streamed_quote/streamed_quote.cpp" // DB::StreamedQuote

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::StreamedQuote db_streamed_quote(pg);

  db_streamed_quote.upsert({
      .ask = 195.0,
      .bid = 194.0,
      .symbol = "TSLA",
      .debug = true,
  });

  pg.disconnect();
}
