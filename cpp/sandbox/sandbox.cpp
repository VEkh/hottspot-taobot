#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"                            // Pg
#include "models/streamed_quote/streamed_quote.cpp" // DB::StreamedQuote

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::StreamedQuote db_streamed_quote(pg);

  DB::StreamedQuote::quote_t quote =
      db_streamed_quote.get({.symbol = "TSLA", .debug = true});

  printf("ask: %f • bid: %f • symbol: %s • timestamp: %f\n", quote.ask,
         quote.bid, quote.symbol.c_str(), quote.timestamp);

  pg.disconnect();
}
