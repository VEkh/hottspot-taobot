#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include <fstream>           // std::ifstream, std::ios
#include <locale.h>          // setlocale
#include <math.h>            // abs
#include <stdexcept>         // std::invalid_argument
#include <stdio.h>           // printf
#include <string>            // std::string
#include <valarray>          // std::valarray

namespace ETrade {
namespace Returns {
json load() {
  std::string path = std::string(APP_DIR) + "/data/etrade/returns.json";
  std::ifstream file(path.c_str(), std::ios::in);

  if (!file.good()) {
    std::string error_message = Formatted::error_message(
        "Returns data missing at " + std::string(path));

    throw std::invalid_argument(error_message);
  }

  json returns_json;
  file >> returns_json;

  return returns_json;
}

void log() {
  json returns = load();

  char (*sign)(double) = [](double n) -> char { return n >= 0 ? '+' : '-'; };

  const std::valarray<double> all_returns = returns["all"];
  const std::valarray<double> week_returns = returns["week"];

  const double total = all_returns.sum();
  const double week_total = week_returns.sum();

  setlocale(LC_NUMERIC, "");
  printf("* Week's Return: %c$%'.2f\n", sign(week_total), abs(week_total));
  printf("* Total Return: %c$%'.2f\n", sign(total), abs(total));
}
} // namespace Returns
} // namespace ETrade
