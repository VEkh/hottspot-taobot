#ifndef ALPACA__PERFORMANCE_LOGGER_read_json_file
#define ALPACA__PERFORMANCE_LOGGER_read_json_file

#include "deps.cpp"  // json
#include "logger.h"  // Alpaca::Performance::Logger
#include <fstream>   // std::ifstream, std::ios
#include <stdexcept> // std::invalid_argument
#include <string>    // std::string

json Alpaca::Performance::Logger::read_json_file(const std::string filepath) {
  std::string path = std::string(DATA_DIR) + std::string("/alpaca/") + filepath;

  std::ifstream file(path.c_str(), std::ios::in);

  if (!file.good()) {
    std::string error_message = Formatted::error_message(
        "Returns data missing at " + std::string(path));

    throw std::invalid_argument(error_message);
  }

  json returns_json;
  file >> returns_json;
  file.close();

  return returns_json;
}

#endif
