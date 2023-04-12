#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/utils/time.cpp" // ::utils::time_
#include <time.h>             // time

int main(int argc, char *argv[]) {
  const long int now = time(nullptr);
  const double today_start_epoch =
      ::utils::time_::beginning_of_day_to_epoch(now);

  const long int tomorrow_start = today_start_epoch + (24 * 60 * 60);

  tm local_time = *localtime(&tomorrow_start);
  local_time.tm_hour = 13;
  local_time.tm_min = 30;
  local_time.tm_sec = 0;
  const long int new_epoch = mktime(&local_time);

  printf("%i:%i\n", local_time.tm_hour, local_time.tm_min);
  printf("new_epoch: %li\n", new_epoch);
}
