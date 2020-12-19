#include <iostream> // std::cout, std::endl
#include <string>   // std::string

int main() {
  std::string str = "foo";

  switch (str) {
  case "bar": {
    std::cout << "bar none" << std::endl;
    break;
  }
  case "foo": {
    std::cout << "yerrr" << std::endl;
    break;
  }
  }
}
