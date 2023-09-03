#if !defined CURL_CLIENT_log_request
#define CURL_CLIENT_log_request

#include "curl_client.h"     // CurlClient, stream_format
#include "lib/formatted.cpp" // Formatted
#include "to_string.cpp"     // to_string
#include <iostream>          // std::cout, std::endl

void CurlClient::log_request() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.yellow;
  std::cout << std::endl << to_string() << std::endl;
  std::cout << fmt.reset << std::endl;
}

#endif
