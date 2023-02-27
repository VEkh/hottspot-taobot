#ifndef UTILS__IO
#define UTILS__IO

#include "lib/formatted.cpp" // Formatted
#include "string.cpp"        // ::utils::string
#include <fstream>           // std::ifstream, std::ios, std::ofstream
#include <map>               // std::map
#include <regex>     // std::regex, std::regex_search, std::regex_token_iterator
#include <stdexcept> // std::invalid_argument, std::runtime_error
#include <stdio.h>   // fgets, popen
#include <string>    // std::getline, std::string
#include <utility>   // std::pair
#include <vector>    // std::vector

namespace utils {
namespace io {
template <typename TransformPredicate>
std::vector<std::string> collect_args(int argc, char **argv,
                                      TransformPredicate fn) {
  return collect_args(argc, argv, &fn);
}

template <typename TransformPredicate>
std::vector<std::string> collect_args(int argc, char **argv,
                                      TransformPredicate *fn) {
  std::vector<std::string> args;

  for (int i = 2; i < argc; i++) {
    const std::string arg = (*fn)(argv[i]);
    args.push_back(arg);
  }

  return args;
}

std::vector<std::string> collect_args(int argc, char **argv) {
  return collect_args(argc, argv,
                      [](std::string in) -> std::string { return in; });
}

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

std::ifstream read_file(const char *filepath) {
  std::ifstream file(filepath, std::ios::in);

  if (!file.good()) {
    std::string error_message =
        Formatted::error_message(std::string("File missing at ") + filepath);

    throw std::invalid_argument(error_message);
  }

  return file;
}

std::string system_exec(const char *cmd) {
  char buffer[128];
  std::string result;
  FILE *pipe = popen(cmd, "r");

  if (pipe == nullptr) {
    std::string error;
    error = Formatted::error_message(
        error + "popen() failed while executing '" + cmd + "'");

    throw std::runtime_error(error);
  }

  try {
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
      result += buffer;
    }
  } catch (...) {
    pclose(pipe);

    std::string error;
    error = Formatted::error_message(
        error + "Something went wrong while reading the response from '" + cmd +
        "'");

    throw std::runtime_error(error);
  }

  pclose(pipe);
  return result;
}

std::string system_exec(const std::string &cmd) {
  return system_exec(cmd.c_str());
}

std::vector<std::string> tradeable_symbols(const std::string project) {
  const std::string symbols_file_path =
      std::string(APP_DIR) + "/bin/" + project + "/symbols";

  std::ifstream file(symbols_file_path.c_str(), std::ios::in);
  std::string line;
  std::vector<std::string> out;

  while (std::getline(file, line)) {
    out.push_back(line);
  }

  return out;
}

void write_to_file(std::string body, const char *file_path) {
  std::ofstream output_file(file_path, std::ios::out | std::ios::trunc);
  output_file << body;
  output_file.close();
}
} // namespace io
} // namespace utils

#endif
