#include "utils/debugger.cpp" // utils::debugger::inspect_type
#include <iostream>           // std::cout

int main() {
  char *str = nullptr;
  std::string type = utils::debugger::inspect_type(typeid(str).name());
  std::cout << type << std::endl;
}
