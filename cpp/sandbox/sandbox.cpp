#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <ctime>  // std::time
#include <math.h> // INFINITY

int main() {
  size_t size = 1;

  double started_at = std::time(nullptr) - 100;

  printf("Started At: %.2f • Time Elapsed: %.2f\n", started_at,
         std::time(nullptr) - started_at);
}
