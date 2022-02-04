#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/time.cpp"
#include <locale.h> // setlocale
#include <math.h>

int main() {
  std::time_t now = std::time(nullptr);
  printf("Is end of day: %s\n",
         ::utils::time_::date_string(&now, "%c %Z").c_str());
}
