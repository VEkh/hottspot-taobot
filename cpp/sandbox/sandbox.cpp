#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <map> // std::map

int main() {
  char *symbol = "GBP_USD";

  std::map<const char *, double> SPREAD_LIMITS = {
      {"EUR_JPY", 2.0e-2},
      {"EUR_USD", 1.6e-4},
      {"GBP_USD", 2.0e-4},
  };

  printf("Spread limit for %s is: %.6f\n", symbol, SPREAD_LIMITS[symbol]);
  printf("Less than or equal to zero?: %i\n", SPREAD_LIMITS[symbol] <= 0);
}
