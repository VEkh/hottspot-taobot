#include <iostream> // std::cout, std::endl
#include <list>     // std::list
#include <map>      // std::map
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/nyse_availability/nyse_availability.cpp" // NyseAvailability

int main(int argc, char *argv[]) {
  NyseAvailability nyse_availability;

  double epoch = 1721344263.037384;
  epoch = 1721314800.000000;
  epoch = 1720105200.000000;
  epoch = 1647356400.000000;

  printf("is market open: %i\n", nyse_availability.is_market_open(epoch));
}
