#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <unistd.h> // usleep

#include <chrono> // std::chrono

int main() {
  usleep(3 * 1000 * 1000);
  printf("I slept for 3 seconds\n");
}
