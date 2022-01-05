#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "deps.cpp" // json
#include <string>   // std::stoi

int main() {
  json j = R"(
    {
      "foo": null
    }
  )"_json;

  if (j["foo"] == nullptr) {
    printf("yeet\n");
  }
}
