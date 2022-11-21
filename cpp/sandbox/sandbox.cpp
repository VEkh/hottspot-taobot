#include <ctime>    // std::time
#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

int main() {
  const int bool_int = 4 % 2 == 0;
  const long int now = std::time(nullptr);
  const std::string str = "fo";
  const char *chars = "foo";

  std::time_t local_now;
  std::time(&local_now);
  std::tm local_time = *std::localtime(&local_now);

  printf("Num: %li\n", now + bool_int);
  printf("Day: %i\n", local_time.tm_mday);
  printf("Minute: %i\n", local_time.tm_min);
  printf("Same String?: %i\n", str == std::string(chars));
}
