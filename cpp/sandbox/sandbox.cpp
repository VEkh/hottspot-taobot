#include "src/utils/debugger.cpp" // utils::debugger::inspect
#include "src/utils/string.cpp"   // utils::string::split
#include <any>                    // std::any
#include <iostream>               // std::cout, std::endl
#include <map>                    // std::map
#include <string>                 // std::string
#include <vector>                 // std::vector

int main() {
  std::vector<std::string> strs = {};
  std::string str;

  if (strs.size() > 0) {
    str = strs[0];
  }

  std::cout << "str: " << str << std::endl;
}
