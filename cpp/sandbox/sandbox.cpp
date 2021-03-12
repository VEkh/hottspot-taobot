#include <iomanip> // std::setfill, std::setw
#include <iostream>
#include <sstream> // std::stringstream
#include <string>  // std::string

std::string seconds_to_time(const int in_seconds) {
  std::ostringstream out;

  const int minutes = in_seconds / 60;
  const int seconds = in_seconds % 60;

  out << std::setfill('0') << std::setw(2) << minutes << ":"
      << std::setfill('0') << std::setw(2) << seconds;

  return out.str();
}

int main() { std::cout << seconds_to_time(59) << std::endl; }
