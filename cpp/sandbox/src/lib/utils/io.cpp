#ifndef UTILS__IO
#define UTILS__IO

#include <fstream> // std::ios, std::ofstream
#include <map>     // std::map
#include <regex>   // std::regex, std::regex_search, std::regex_token_iterator
#include <string>  // std::string
#include <utility> // std::pair

namespace utils {
namespace io {
std::pair<std::string, std::string> flag_to_pair(std::string &flag) {
  std::regex token_regex = std::regex("--|=");

  std::sregex_token_iterator it(flag.begin(), flag.end(), token_regex, -1);
  std::sregex_token_iterator end;

  std::string parts[2] = {"", "1"};
  int parts_i = 0;

  for (; it != end; it++) {
    if (((std::string)*it).empty()) {
      continue;
    }

    parts[parts_i] = *it;

    parts_i++;
  }

  return {parts[0], parts[1]};
}

std::map<std::string, std::string> extract_flags(int argc, char **argv) {
  std::map<std::string, std::string> flags;

  for (int i = 0; i < argc; i++) {
    std::string arg = argv[i];

    if (!std::regex_search(arg, std::regex("^--.*"))) {
      continue;
    }

    std::pair<std::string, std::string> flag_parts = flag_to_pair(arg);
    flags.insert(flag_parts);
  }

  return flags;
}

void write_to_file(std::string body, const char *file_path) {
  std::ofstream output_file(file_path, std::ios::out | std::ios::trunc);
  output_file << body;
  output_file.close();
}
} // namespace io
} // namespace utils

#endif
