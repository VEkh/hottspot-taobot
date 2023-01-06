#include <ctime>    // std::time
#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string
#include <vector>   // std::vector

int main() {
  const std::vector<std::string> nums = {"very", "superstitious"};

  for (const std::string n : nums) {
    std::cout << n << std::endl;
  }
}
