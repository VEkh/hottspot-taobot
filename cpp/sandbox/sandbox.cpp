#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <iomanip> // std::get_time
#include <sstream> // std::stringstream
#include <string>

int main() {
  std::tm time = {};

  std::string date_string_string = "2022-01-31";
  std::istringstream date_string(date_string_string);

  date_string >> std::get_time(&time, "%Y-%m-%d");
  std::mktime(&time);

  printf("Day of week: %i\n", time.tm_wday);

  std::cout << std::put_time(&time, "%F") << std::endl;
}
