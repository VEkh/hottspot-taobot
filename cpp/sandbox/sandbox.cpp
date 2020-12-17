#include "lib/utils/string.cpp" // utils::string
#include <iostream>             // std::cout, std::endl
#include <string>               // std::string

void log(std::string str) { std::cout << "\"" << str << "\"" << std::endl; }

int main() {
  std::string str = "    \r\t\nfo o bar is the shiznit\r \n\n\t";

  str = utils::string::trim(str);
  log(str);
}
