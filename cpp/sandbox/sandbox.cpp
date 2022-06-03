#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/time.cpp" // ::utils::time_
#include <ctime>              // std::tm, std::mktime

int main() {
  const char *time_str = "2022-06-03T13:56:41.421263872Z";
  std::tm parsed_time =
      ::utils::time_::parse_timestamp(time_str, "%Y-%m-%dT%H:%M:%SZ");
  const std::time_t epoch = std::mktime(&parsed_time);

  const std::time_t now = std::time(nullptr);

  printf("parsed_time: %i\n", (int)epoch);
  printf("now: %i\n", (int)now);
  printf("is stale: %i\n", (int)(now - epoch) > 10);
}
