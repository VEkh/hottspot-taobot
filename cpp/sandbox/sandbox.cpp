#include "lib/utils/float.cpp" // ::utils::float_
#include <algorithm>
#include <iostream> // std::cout, std::endl
#include <regex>    // std::regex, std::regex_search
#include <stdio.h>  // printf, puts

int main() {
  const double max_target = 0.0355;
  const double min_target = 0.0055;
  const double one_hour_seconds = 60 * 60;
  const int runtime_ = 2.25 * one_hour_seconds;

  const int breakpoint_seconds = 2 * one_hour_seconds;
  const double hours_past_breakpoint =
      std::max(0.0, (runtime_ - breakpoint_seconds) / one_hour_seconds);

  const double y = ::utils::float_::sigmoid(max_target, min_target,
                                            hours_past_breakpoint, -6.5, 1);

  printf("y: %.4f • hours_past_breakpoint: %.3f • breakpoint_seconds: %i\n", y,
         (runtime_ - breakpoint_seconds) / one_hour_seconds,
         breakpoint_seconds);
}
