#include <iostream> // std::cout, std::endl
#include <list>     // std::list
#include <map>      // std::map
#include <stdio.h>  // printf
#include <string>   // std::string

#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "lib/pg/pg.cpp"                    // Pg

int main(int argc, char *argv[]) {
  Pg pg((std::map<std::string, std::string>){
      {"env", "backtest"},
  });

  pg.connect();

  DB::AccountStat db_account_stat(pg);

  const DB::AccountStat::account_snapshot_t snapshot =
      db_account_stat.get_snapshot({
          .api_key_id = "backtest-0",
          .debug = false,
          .starting_from = 1711584000.000000,
      });

  printf("Equity: %.2f • Original: %.2f • Max: %.2f • Min: %.2f\n",
         snapshot.equity, snapshot.original_equity, snapshot.max_equity,
         snapshot.min_equity);

  pg.disconnect();
}
