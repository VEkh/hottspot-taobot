#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/pg/pg.cpp" // Pg
#include <future>        // std::future
#include <time.h>        // time
#include <unistd.h>      // usleep

void poll_notice(Pg pg) {
  while (true) {
    usleep(1e6);

    pg.exec(
        "select pg_notify('backtest-pos_2_5__61-clock', '1687413552.00000')",
        true);
  }
}

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  while (true) {
    const std::string notification = pg.await_notification({
        .channel = "backtest-pos_2_5__61-clock",
        .debug = true,
    });

    std::cout << "Notification: " << notification << std::endl;
  }

  poll_notice(pg);

  pg.disconnect();
}
