#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "lib/pg/pg.cpp"                    // Pg

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  std::list<DB::AccountStat::account_snapshot_t> arr;

  DB::AccountStat db_account_stat(pg);

  std::list<DB::AccountStat::account_snapshot_t> snapshots =
      db_account_stat.get_daily_snapshots("AKC4P5UKCWADG8WE6ZEV");

  DB::AccountStat::account_snapshot_t snapshot = snapshots.back();

  printf("equity: %f\n", snapshot.equity);

  pg.disconnect();
}
