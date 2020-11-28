#if !defined UTILS__DEBUGGER
#define UTILS__DEBUGGER

#include <cxxabi.h> // abi::__cxa_demangle
#include <iostream> // std::cout, std;:endl
#include <map>      // std::map
#include <string>   // std::string
#include <vector>   // std::vector

namespace utils {
namespace debugger {
void inspect(std::string str) { std::cout << str << std::endl; }

void inspect(std::vector<std::string> collection) {
  for (int i = 0; i < collection.size(); i++) {
    std::cout << collection[i] << std::endl;
  }
}

void inspect(std::map<std::string, std::string> collection) {
  std::map<std::string, std::string>::iterator it;

  if (collection.begin() == collection.end()) {
    return;
  }

  std::cout << "{" << std::endl;

  for (it = collection.begin(); it != collection.end(); it++) {
    std::cout << "  " << it->first << ": " << it->second << "," << std::endl;
  }

  std::cout << "}" << std::endl;
}

/* @param type_name: typeid(obj).name() */
std::string inspect_type(const char *type_name) {
  int status;
  char *demangled_name = abi::__cxa_demangle(type_name, NULL, NULL, &status);
  return std::string(demangled_name);
}
} // namespace debugger
} // namespace utils
#endif
