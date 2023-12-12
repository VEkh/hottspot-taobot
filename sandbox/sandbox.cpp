#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "deps.cpp"           // json
#include "lib/utils/json.cpp" // ::utils::json

int main(int argc, char *argv[]) {
  std::string input = "empty";
  json j;

  try {
    j = ::utils::json::parse_with_catch(input, "sandbox");
  } catch (...) {
    printf("🎉\n");
  }

  printf("input: %s\n", j.dump().c_str());
}
