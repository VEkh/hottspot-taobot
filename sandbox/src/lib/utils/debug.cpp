#ifndef UTILS__DEBUG
#define UTILS__DEBUG

#include <cxxabi.h> // abi::__cxa_demangle
#include <iostream> // std::cout, std;:endl
#include <map>      // std::map
#include <string>   // std::string

namespace utils {
namespace debug {
template <typename BasicType> void inspect(BasicType in) {
  std::cout << in << std::endl;
}

template <typename Key, typename Value>
void inspect(std::map<Key, Value> collection) {
  typename std::map<Key, Value>::iterator it;

  if (collection.begin() == collection.end()) {
    return;
  }

  std::cout << "{" << std::endl;

  for (it = collection.begin(); it != collection.end(); it++) {
    std::cout << "  \"" << it->first << "\": \"" << it->second << "\","
              << std::endl;
  }

  std::cout << "}" << std::endl;
}

/* @param type_name: typeid(obj).name() */
std::string inspect_type(const char *type_name) {
  int status;
  char *demangled_name = abi::__cxa_demangle(type_name, NULL, NULL, &status);
  return std::string(demangled_name);
}
} // namespace debug
} // namespace utils
#endif
