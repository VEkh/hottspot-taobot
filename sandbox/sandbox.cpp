#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "db/utils/utils.cpp" // DB::Utils
#include "lib/pg/pg.cpp"      // Pg
#include "lib/utils/time.cpp" // ::utils::time_

int main(int argc, char *argv[]) {
  Pg pg;
  pg.connect();

  DB::Utils db_utils(pg);

  const double tomorrow = time(nullptr) + (24 * 60 * 60);
  std::string tomorrow_date_string =
      ::utils::time_::date_string(tomorrow, "%F", "America/Chicago");

  printf("tomorrow: %f • tomorrow string: %s\n", tomorrow,
         tomorrow_date_string.c_str());

  const double epoch = db_utils.timestamp_to_epoch(
      tomorrow_date_string + " 08:30:00", "America/Chicago");

  printf("Epoch: %f\n", epoch);

  pg.disconnect();
}
