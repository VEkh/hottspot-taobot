#include "src/utils/debugger.cpp" // utils::debugger::inspect
#include "src/utils/string.cpp"   // utils::string::split
#include <iostream>               // std::cout, std::endl
#include <string>                 // std::string
#include <vector>                 // std::vector

int main() {
  std::vector<std::string> split_string;

  split_string = utils::string::split("foo;bar;baz", ";");

  utils::debugger::inspect(split_string);

  split_string =
      utils::string::split("https://example.com?foo=foo&bar=bar", "?");

  utils::debugger::inspect(split_string);
}
