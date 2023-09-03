#if !defined CURL_CLIENT_method_to_string
#define CURL_CLIENT_method_to_string

#include "curl_client.h" // CurlClient, HTTP_METHODS, http_method_t
#include <string>        // std::string

std::string CurlClient::method_to_string(http_method_t method_t) {
  return HTTP_METHODS[method_t];
}

#endif
