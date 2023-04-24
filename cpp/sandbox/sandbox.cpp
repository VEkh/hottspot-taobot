#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include <regex> // std::regex

int main(int argc, char *argv[]) {
  const std::string str = "backtest-pos_2_5__62";
  std::smatch match;

  std::regex_search(str, match, std::regex("-pos_(.+)__(.+)-act")) ||
      std::regex_search(str, match, std::regex("-pos_(.+)__(.+)$"));

  printf("match 1: %s • match 2: %s\n", match[1].str().c_str(),
         match[2].str().c_str());
}
