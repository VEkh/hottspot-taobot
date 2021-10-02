#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include "deps.cpp"
#include <map>

int main() {
  json j;

  if (j["code"] == 1) {
    printf("Yerrr\n");
  }
}
