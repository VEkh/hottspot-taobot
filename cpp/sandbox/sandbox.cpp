#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"          // Pg
#include "models/quote/quote.cpp" // DB::Quote
#include <map>                    // std::map
#include <string>                 // std::string

int main(int argc, char *argv[]) {
  Pg pg((std::map<std::string, std::string>){{"env", "production"}});
  pg.connect();

  DB::Quote db_quote(pg);

  const double stop_profit = db_quote.get_stop_profit("TSLA", true);

  printf("stop_profit: %f\n", stop_profit);

  pg.disconnect();
}
