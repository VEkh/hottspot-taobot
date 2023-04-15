#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include <time.h>

int main(int argc, char *argv[]) {
  time_t now = time(nullptr);
  tm now_tm = *localtime(&now);

  const int week_of_year = (now_tm.tm_yday - now_tm.tm_wday + 7) / 7;

  printf("yday: %i • wday: %i\n", now_tm.tm_yday, now_tm.tm_wday);
  printf("week_of_year: %i\n", week_of_year);
}
