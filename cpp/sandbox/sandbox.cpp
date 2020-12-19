#include <iostream> // std::cout, std::endl
#include <string>   // std::string

const char *fallback() { return "skrilla"; }

void fn(const char *required) { fn(required, fallback()) }

void fn(const char *required, const char *optional) {
  std::cout << "required: " << required << std::endl;
  std::cout << "optional: " << optional << std::endl;
}

int main() { fn("yerrr"); }
