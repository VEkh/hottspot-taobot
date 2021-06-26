#ifndef ETRADE__CLIENT_handle_place_order_error
#define ETRADE__CLIENT_handle_place_order_error

#include "client.h"                          // ETrade::Client, stream_format
#include "etrade/constants.cpp"              // ETrade::constants
#include "etrade/deps.cpp"                   // json
#include "is_account_key_error_response.cpp" // is_account_key_error_response
#include "is_not_shortable_response.cpp"     // is_not_shortable_response
#include "lib/curl_client/curl_client.h"     // CurlClient
#include "lib/formatted.cpp"                 // Formatted
#include "lib/utils/string.cpp"              // utils::string
#include <iostream>                          // std::cout, std::endl

CurlClient
ETrade::Client::handle_place_order_error(const CurlClient &curl_client,
                                         const order_action_t &order_action,
                                         const std::string &action) {
  json response_body = json::parse(curl_client.response.body);

  if (response_body.contains(action + "OrderResponse")) {
    return curl_client;
  }

  if (is_account_key_error_response(curl_client)) {
    return curl_client;
  }

  if (is_not_shortable_response(curl_client)) {
    return curl_client;
  }

  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.red;
  std::cout << "❌ Something went wrong while trying to "
            << utils::string::downcase(action) << " the "
            << ETrade::constants::ORDER_ACTIONS[order_action]
            << " order: " << std::endl;
  std::cout << response_body.dump(2) << std::endl;
  std::cout << fmt.reset;

  exit(1);
}

#endif
