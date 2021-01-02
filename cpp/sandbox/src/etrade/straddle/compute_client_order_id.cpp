#if !defined ETRADE__STRADDLE_compute_client_order_id
#define ETRADE__STRADDLE_compute_client_order_id

#include "etrade/oauth_header/oauth_header.cpp" // ETrade::OAuthHeader
#include "lib/utils/time.cpp"                   // utils::time
#include "straddle.h" // ETrade::Straddle, etrade_client
#include <string>     // string

std::string
ETrade::Straddle::compute_client_order_id(const std::string key_base) {
  ETrade::OAuthHeader oauth_header;

  std::string nonce_key =
      std::to_string(utils::time::epoch("nanoseconds")) + key_base;

  return oauth_header.compute_nonce(nonce_key).substr(0, 20);
}

#endif
