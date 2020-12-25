#if !defined ETRADE__STRADDLE_compute_client_order_id
#define ETRADE__STRADDLE_compute_client_order_id

#include "etrade/oauth_header/oauth_header.cpp" // ETrade::OAuthHeader
#include "straddle.h" // ETrade::Straddle, etrade_client
#include <string>     // string

std::string ETrade::Straddle::compute_client_order_id() {
  ETrade::OAuthHeader oauth_header;
  return oauth_header.compute_nonce().substr(0, 20);
}

#endif
