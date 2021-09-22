#if !defined ETRADE__CLIENT_compute_client_order_id
#define ETRADE__CLIENT_compute_client_order_id

#include "client.h"                             // ETrade::Client
#include "etrade/oauth_header/oauth_header.cpp" // ETrade::OAuthHeader
#include "lib/utils/time.cpp"                   // utils::time_
#include <string>                               // string

std::string
ETrade::Client::compute_client_order_id(const std::string key_base) {
  ETrade::OAuthHeader oauth_header;

  std::string nonce_key =
      std::to_string(::utils::time_::epoch("nanoseconds")) + key_base;

  return oauth_header.compute_nonce(nonce_key).substr(0, 20);
}

#endif
