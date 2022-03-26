#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <string> //std::getline, std::string

int main() {
  const char *chars = "foo";
  std::string str = "foo";

  printf("Equal?: %i\n", chars == str);
}
