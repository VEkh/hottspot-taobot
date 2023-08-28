#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/utils/time.cpp" // ::utils::time_
#include <list>               // std::list

int main(int argc, char *argv[]) {
  std::list<int> nums = {1, 2, 3};

  std::list<int>::iterator it;

  it = nums.begin();
  std::cout << "it: " << &(*it) << std::endl;

  printf("first: %i\n", *it);
  it++;
  printf("second: %i\n", *it);
}
