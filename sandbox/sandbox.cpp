#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include <time.h> // localtime, mktime, time, tm

int main(int argc, char *argv[]) {
  const int min = 58;

  const int closed_at_min = ((min + 5) / 5) * 5;
  const int opened_at_min = (min / 5) * 5;

  printf("opened_at min: %i\n", opened_at_min);
  printf("closed_at min: %i\n", closed_at_min);

  const long int epoch = 1695845408.010215;
  tm epoch_tm = *localtime(&epoch);

  epoch_tm.tm_min = 60;

  printf("epoch at 60th min: %li\n", (long int)mktime(&epoch_tm));
}
