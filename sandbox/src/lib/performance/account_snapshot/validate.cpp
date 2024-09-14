#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT_validate
#define PERFORMANCE__ACCOUNT_SNAPSHOT_validate

#include "account_snapshot.h" // Performance::AccountSnapshot
#include "lib/formatted.cpp"  // Formatted
#include <stdexcept>          // std::invalid_argument
#include <string>             // std::string

void Performance::AccountSnapshot::validate() {
  if (this->config.api_name.empty()) {
    const std::string message =
        Formatted::error_message("Please specify an api (--api=<API_NAME>).");

    throw std::invalid_argument(message);
  }
}

#endif
