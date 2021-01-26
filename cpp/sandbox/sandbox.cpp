#include <iostream>
#include <time.h>

int main() {
  time_t timer;
  time(&timer);
  std::cout << timer << std::endl;
}
