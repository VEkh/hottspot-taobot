#include "lib/utils/io.cpp" // utils::io
#include <iostream>

int main(int argc, char *argv[]) {
  std::map<std::string, std::string> flags =
      utils::io::extract_flags(argc, argv);

  std::cout << flags["normalize-quantity"] << std::endl;
}
