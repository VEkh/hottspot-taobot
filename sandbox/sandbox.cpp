#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "db/candle/candle.cpp" // DB::Candle
#include "lib/pg/pg.cpp"        // Pg
#include <list>                 // std::list

int main(int argc, char *argv[]) {
  Pg conn;
  conn.connect();

  DB::Candle candle(conn, 1, "AMZN");

  std::list<DB::Candle::candle_t> candles =
      candle.get_latest(1697486400.000000);

  for (DB::Candle::candle_t candle : candles) {
    printf("%s\n", candle.color().c_str());
  }

  conn.disconnect();
}
