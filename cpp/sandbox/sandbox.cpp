#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/time.cpp"
#include <map>
#include <stdlib.h>
#include <time.h>

int main() {
  std::map<const char *, int> results = {
      {"H", 0},
      {"T", 0},
  };

  const char *coin[] = {"H", "T"};

  srand(::utils::time_::epoch("nanoseconds"));

  for (int i = 0; i < 1e7; i++) {
    const int side_index = rand() % 2;
    const char *coin_side = coin[side_index];

    results[coin_side]++;
  }

  const double sum = results["H"] + results["T"];

  printf("H: %i (%.5f%%) • T: %i (%.f%%) \n", results["H"],
         100 * results["H"] / sum, results["T"], 100 * results["T"] / sum);
}
