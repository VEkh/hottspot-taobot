#include <iostream> // std::cout, std::endl
#include <stdexcept>
#include <stdio.h> // printf
#include <string>

int main() {
  std::string msg = std::string("I like to say ") + std::string(__FILE__) +
                    std::to_string(__LINE__);

  throw std::runtime_error(msg);
  printf("%s\n", msg.c_str());
}
