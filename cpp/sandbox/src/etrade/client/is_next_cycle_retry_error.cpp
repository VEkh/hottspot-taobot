#ifndef ETRADE__CLIENT_is_next_cycle_retry_error
#define ETRADE__CLIENT_is_next_cycle_retry_error

#include "client.h"                      // ETrade::Client, stream_format
#include "lib/curl_client/curl_client.h" // CurlClient
#include "lib/utils/json.cpp"            // ::utils::json
#include <map>                           // std::map

bool ETrade::Client::is_next_cycle_retry_error(CurlClient &curl_client) {
  json response_body = ::utils::json::parse_with_catch(
      curl_client.response.body, "ETRADE__CLIENT_is_next_cycle_retry_error");

  if (!response_body.contains("Error")) {
    return false;
  }

  if (!response_body["Error"].contains("code")) {
    return false;
  }

  const std::map<int, const char *> error_codes = {
      {100, "ACCOUNT_KEY_MISSING"},
      {101, "NUMBER_OF_SHARES_MISSING"},
      {3010, "INSUFFICIENT_FUNDS"},
      {33, "NOT_SHORTABLE"},
  };

  const int code = response_body["Error"]["code"];

  if (error_codes.find(code) != error_codes.end()) {
    curl_client.response.error_code = code;
    return true;
  }

  return false;
}

#endif
