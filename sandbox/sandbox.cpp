#include <iostream> // std::cout, std::endl
#include <regex>    // std::regex, std::regex_search, std::smatch
#include <stdio.h>  // printf
#include <string>   // std::string

int main(int argc, char *argv[]) {
  std::string symbol = "USD_JPY";

  std::smatch match;
  std::regex_search(symbol, match, std::regex("^(\\w+)_(\\w+)$"));

  std::smatch::iterator it;

  for (it = match.begin(); it != match.end(); it++) {
    if (it == match.begin()) {
      continue;
    }

    printf("match: %s", it->str().c_str());
    std::cout << std::endl;
  }
}
