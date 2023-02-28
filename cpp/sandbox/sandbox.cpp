#include <ctime>    // std::time
#include <iostream> // std::cout, std::endl
#include <math.h>   // INFINITY
#include <stdio.h>  // printf
#include <string>   // std::string
#include <vector>   // std::vector

std::vector<int> limiter(const double limit = INFINITY) {
  const std::vector<int> full = {1, 2, 3, 4, 5};

  std::vector<int>::const_iterator range_begin =
      limit == INFINITY ? full.begin() : full.end() - limit;

  const std::vector<int> out = std::vector<int>(range_begin, full.end());

  return out;
}

int main() {
  const std::vector<int> nums = limiter(2);

  for (const int n : nums) {
    std::cout << n << std::endl;
  }
}
