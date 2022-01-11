#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <string> // std::string

/*
 * std::cmatch
 * std::regex
 * std::regex_constants
 * std::regex_search
 */
#include <regex>

std::string base_currency() {
  const char *symbol = "AUD_USD";
  std::cmatch match;
  std::regex_search(symbol, match, std::regex("^(\\w+)_\\w+$"));

  return match[1];
}

int main() { printf("%s\n", base_currency().c_str()); }
