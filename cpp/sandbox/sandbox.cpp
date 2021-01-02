#include "deps.cpp"
#include <iostream>
#include <string>

int main() {
  std::string str = "null";
  std::cout << json::parse(str).is_null() << std::endl;
}
