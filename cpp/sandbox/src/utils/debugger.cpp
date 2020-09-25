#include <iostream> // std::cout, std;:endl;
#include <vector>   // std::vector

namespace utils {
namespace debugger {
int inspect(std::vector<std::string> collection) {
  for (int i = 0; i < collection.size(); i++) {
    std::cout << collection[i] << std::endl;
  }
}
} // namespace debugger
} // namespace utils
