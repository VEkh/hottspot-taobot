#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include <regex>  // std::regex, std::regex_search
#include <string> // std::string

int main() {
  const char *symbol = "aapl";
  const char *test = "AAPL.json";
  std::cmatch match;

  if (std::regex_search(
          test, match,
          std::regex("(\\w+)\\.json", std::regex_constants::icase))) {
    printf("match size: %i\n", (int)match.size());
    printf("match 0: %s\n", std::string(match[1]).c_str());
  }
}
