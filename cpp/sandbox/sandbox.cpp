#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp"                // Pg
#include "models/position/position.cpp" // DB::Position
#include <time.h>                       // time

int main(int argc, char *argv[]) {
  const double now = time(nullptr);
  Pg pg;
  pg.connect();

  DB::Position db_position(pg);

  db_position.insert({
      .api_key_id = "PKB5FJN28HVP0TNZV00B",
      .close_order_execution_mid = 100.00,
      .close_order_id = "abcdef123456",
      .close_order_quantity = -10.00,
      .closed_at = now,
      .max_profit = 120.00,
      .max_profit_at = now,
      .open_order_execution_mid = 110.00,
      .open_order_id = "abcdef123456",
      .open_order_quantity = 10.00,
      .opened_at = now,
      .stop_loss = 90.00,
      .stop_profit = 110.00,
      .symbol = "TSLA",
      .debug = true,
  });

  pg.disconnect();
}
