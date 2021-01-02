#if !defined ETRADE__STRADDLE_handle_request_error
#define ETRADE__STRADDLE_handle_request_error

#include "etrade/deps.cpp"               // json
#include "lib/curl_client/curl_client.h" // CurlClient
#include "lib/formatted.cpp"             // Formatted
#include "lib/utils/string.cpp"          // utils::string
#include "straddle.h" // ETrade::Straddle, ORDER_ACTIONS, stream_format
#include <iostream>   // std::cout, std::endl

CurlClient
ETrade::Straddle::handle_request_error(const CurlClient &curl_client,
                                       const order_action_t &order_action,
                                       const std::string &action) {
  json response_body = json::parse(curl_client.response.body);

  if (response_body.contains(action + "OrderResponse")) {
    return curl_client;
  }

  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.red;
  std::cout << "❌ Something went wrong while trying to "
            << utils::string::downcase(action) << " the "
            << ORDER_ACTIONS[order_action] << " order: " << std::endl;
  std::cout << response_body.dump(2) << std::endl;
  std::cout << fmt.reset;

  exit(1);
}

#endif
