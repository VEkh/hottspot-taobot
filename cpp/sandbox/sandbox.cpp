#include "src/utils/debugger.cpp" // utils::debugger::inspect
#include <cstring>                // std::string
#include <sstream>                // std::stringstream
#include <string>                 // std::string

struct foo {
  const char *body;
};

int main() {
  foo bar;
  bar.body = "baz";

  utils::debugger::inspect(bar.body);
}
