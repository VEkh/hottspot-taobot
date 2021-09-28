#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include "deps.cpp"

int main() {
  json j;

  if (!j.contains("foo")) {
    printf("yerrr\n");
  }
}
