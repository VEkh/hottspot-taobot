#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "db/backtest_clock/backtest_clock.cpp" // DB::BacktestClock
#include "lib/pg/pg.cpp"                        // Pg
#include <time.h>                               // time

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::BacktestClock db_backtest_clock(pg);

  const double now = time(nullptr);

  db_backtest_clock.upsert({
      .api_key_id = "backtest-pos_2_5__61",
      .set_to = now,
      .symbol = "TSLA",
      .debug = true,
  });

  const int length = db_backtest_clock
                         .get_all({
                             .api_key_id = "backtest-pos_2_5__61",
                             .set_to = now,
                             .debug = true,
                         })
                         .size();

  printf("clocks: %i\n", length);

  pg.disconnect();
}
