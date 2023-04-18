#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include <regex> // std::regex, std::regex_search

int main(int argc, char *argv[]) {
  const std::string str = "backtest_no_stop_profit__62_5";
  std::smatch l_match;
  std::smatch p_match;

  std::regex_search(str, l_match, std::regex("__(.+)$"));
  std::regex_search(str, p_match, std::regex("^backtest_(.+)__"));

  if (l_match.size() > 1) {
    std::string loss_string =
        std::regex_replace(l_match[1].str(), std::regex("_"), ".");

    printf("l_match: %f\n", std::stod(loss_string));
  }

  if (p_match.size() > 1) {
    printf("p_match: %s\n", p_match[1].str().c_str());
  }
}
