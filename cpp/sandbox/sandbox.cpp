#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/time.cpp"
#include <ctime>
#include <exception>
#include <map>
#include <signal.h>
#include <stdlib.h>

int main() {
  std::time_t now = std::time(nullptr);

  printf("Current Unix Timestamp: %li\n", now);
}
