#ifndef PERFORMANCE__LOGGER_validate
#define PERFORMANCE__LOGGER_validate

#include "lib/formatted.cpp" // Formatted
#include "logger.h"          // Performance::Logger
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

void Performance::Logger::validate() {
  if (this->api_name.empty()) {
    const std::string message =
        Formatted::error_message("Please specify an api (--api=<API_NAME>).");

    throw std::invalid_argument(message);
  }
}

#endif
