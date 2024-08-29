#ifndef UTILS__IO
#define UTILS__IO

#include "deps.cpp"          // json
#include "lib/formatted.cpp" // Formatted
#include "string.cpp"        // ::utils::string
#include <cstring>           // strcpy, strlen
#include <fstream>           // std::ifstream, std::ios, std::ofstream
#include <iostream>          // std::cout, std::endl
#include <libgen.h>          // dirname
#include <list>              // std::list
#include <map>               // std::map
#include <regex>     // std::regex, std::regex_replace, std::regex_search
#include <stdexcept> // std::invalid_argument, std::runtime_error
#include <stdio.h>   // fgets, popen, puts
#include <string>    // std::getline, std::string
#include <unistd.h>  // usleep
#include <utility>   // std::pair
#include <vector>    // std::vector

namespace utils {
namespace io {
using json = nlohmann::json;

template <typename TransformPredicate>
std::list<std::string> extract_args(int argc, char **argv,
                                    TransformPredicate fn) {
  return extract_args(argc, argv, &fn);
}

template <typename TransformPredicate>
std::list<std::string> extract_args(int argc, char **argv,
                                    TransformPredicate *fn) {
  std::regex flag_prefix("^--.*");
  std::list<std::string> args;

  for (int i = 1; i < argc; i++) {
    const std::string arg = (*fn)(argv[i]);

    if (!std::regex_search(arg, flag_prefix)) {
      args.push_back(arg);
    }
  }

  return args;
}

std::list<std::string> extract_args(int argc, char **argv) {
  return extract_args(argc, argv,
                      [](std::string in) -> std::string { return in; });
}

std::pair<std::string, std::string> flag_to_pair(std::string &flag) {
  std::string no_first_dashes = std::regex_replace(flag, std::regex("^--"), "");
  std::string no_equal =
      std::regex_replace(no_first_dashes, std::regex("="), " ");

  std::vector<std::string> parts = ::utils::string::split(no_equal, " ");

  const std::string key = parts.at(0);
  const std::string value = parts.size() == 1 ? "1" : parts.at(1);

  return {key, value};
}

std::map<std::string, std::string> extract_flags(int argc, char **argv) {
  std::regex flag_prefix("^--.*");
  std::map<std::string, std::string> flags;

  for (int i = 0; i < argc; i++) {
    std::string arg = argv[i];

    if (!std::regex_search(arg, flag_prefix)) {
      continue;
    }

    std::pair<std::string, std::string> flag_parts = flag_to_pair(arg);
    flags.insert(flag_parts);
  }

  return flags;
}

bool flag_to_bool(const std::string key, const std::string val) {
  if (val.empty()) {
    return false;
  }

  if (key == val) {
    return true;
  }

  if (val == "true") {
    return true;
  }

  return val == "1";
}

json load_config(const std::string project, const std::string api_key) {
  const std::string config_path =
      std::string(APP_DIR) + "/config/" + project + "/credentials.json";

  std::string error_message;

  std::ifstream config_file(config_path.c_str(), std::ios::in);

  if (!config_file.good()) {
    error_message = Formatted::error_message("Config file missing at " +
                                             std::string(config_path));

    throw std::invalid_argument(error_message);
  }

  if (api_key.empty()) {
    error_message = Formatted::error_message(
        "Please provide an --api-key=<API_KEY> option");

    throw std::invalid_argument(error_message);
  }

  json config_json;
  config_file >> config_json;
  config_file.close();

  if (!config_json.contains(api_key)) {
    error_message = Formatted::error_message(
        "There is no entry for the `api-key` \"" + api_key + "\"");

    throw std::invalid_argument(error_message);
  }

  return config_json;
}

void print_newlines(const int n) {
  for (int i = 0; i < n; i++) {
    puts("");
  }

  std::cout << std::flush;
}

std::list<std::string> read_env_symbols(json &config) {
  std::list<std::string> formatted_symbols;
  std::list<std::string> symbols = config["env_symbols"];

  for (const std::string symbol : symbols) {
    formatted_symbols.push_back(::utils::string::upcase(symbol));
  }

  return formatted_symbols;
}

std::ifstream read_file(const std::string filepath) {
  std::ifstream file(filepath.c_str(), std::ios::in);

  if (!file.good()) {
    std::string error_message =
        Formatted::error_message(std::string("File missing at ") + filepath);

    throw std::invalid_argument(error_message);
  }

  return file;
}

json read_file_to_json(const std::string filepath) {
  json out;

  try {
    std::ifstream file = read_file(filepath);
    file >> out;
  } catch (...) {
    std::string error_message = Formatted::error_message(
        std::string("Something went wrong parsing: ") + filepath);

    std::cout << error_message << std::endl;

    usleep(5e5);

    return read_file_to_json(filepath);
  }

  return out;
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

void write_to_file(std::string body, const char *filepath) {
  std::ofstream output_file(filepath, std::ios::out | std::ios::trunc);
  output_file << body;
  output_file.close();
}

void touch(const char *filepath, const std::string content = "") {
  char filepath_copy[strlen(filepath)];
  strcpy(filepath_copy, filepath);

  std::ifstream file(filepath, std::ios::in);

  if (file.good()) {
    return;
  }

  char *directory = dirname((char *)filepath_copy);

  const std::string mkdir_cmd =
      std::string("mkdir -p ") + std::string(directory);

  system_exec(mkdir_cmd.c_str());
  write_to_file(content, filepath);
}
} // namespace io
} // namespace utils

#endif
