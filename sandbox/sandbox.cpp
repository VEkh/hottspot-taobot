#include <iostream> // std::cout, std::endl
#include <list>     // std::list
#include <map>      // std::map
#include <stdio.h>  // printf
#include <string>   // std::string

#include "db/market_close/market_close.cpp" // DB::MarketClose
#include "lib/pg/pg.cpp"                    // Pg
#include "lib/utils/io.cpp"                 // ::utils::io
#include "lib/utils/iterable.cpp"           // ::utils::iterable

int main(int argc, char *argv[]) {
  std::list<std::string> tradeable_symbols =
      ::utils::io::tradeable_symbols("alpaca");

  Pg pg((std::map<std::string, std::string>){
      {"env", "backtest"},
  });

  pg.connect();

  DB::MarketClose db_market_close(pg);

  std::list<std::string> symbols = db_market_close.get_symbols_closed_at({
      .api_key_id = "backtest-1",
      .debug = true,
      .epoch = 1704240000.000000,
  });

  pg.disconnect();

  ::utils::iterable::print(symbols);

  printf("are equal?: %i\n",
         ::utils::iterable::are_equal(symbols, tradeable_symbols));
}
