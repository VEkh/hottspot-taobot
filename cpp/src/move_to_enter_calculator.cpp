#include <cmath>    // std::abs
#include <iostream> // std::cout, std::endl
#include <string>   // std::stof

int main(int argc, char *argv[]) {
  float high = std::stof(argv[2]);
  float low = std::stof(argv[3]);
  float open = std::stof(argv[1]);

  float movement = std::abs(((high - low) / open) * 0.2);

  std::cout << "Target trailing stop percentage is: " << movement * 100.0
            << std::endl;
}
