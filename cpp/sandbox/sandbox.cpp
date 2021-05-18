#include <chrono>
#include <iostream>
#include <thread>
#include <time.h>

int main() {
  time_t now;
  time(&now);

  std::this_thread::sleep_for(std::chrono::seconds(3));

  time_t later;
  time(&later);

  std::cout << (later - now) << std::endl;
}
