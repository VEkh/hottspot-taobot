#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include <iterator> // std::advance
#include <map>      // std::map

int main(int argc, char *argv[]) {
  std::map<int, int> nums = {{1, 1}, {2, 4}, {3, 9}};

  std::map<int, int>::iterator it = nums.begin();
  const int offset = nums.size() - 2;
  std::advance(it, offset);

  for (; it != nums.end(); it++) {
    printf("%i\n", it->second);
  }
}
