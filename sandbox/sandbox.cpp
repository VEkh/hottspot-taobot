#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include <time.h>

int main(int argc, char *argv[]) {
  long int now = time(nullptr);
  tm market_start_tm = *localtime(&now);

  market_start_tm.tm_hour = 13;
  market_start_tm.tm_min = 30;
  market_start_tm.tm_sec = 0;

  const double market_start = mktime(&market_start_tm);

  printf("%f\n", market_start);
}
