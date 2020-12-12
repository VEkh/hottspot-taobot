#if !defined ETRADE__OAUTH_HEADER
#define ETRADE__OAUTH_HEADER

#include "oauth_header.h" // ETrade::OAuthHeader, props_t
#include "build.cpp"
#include "compute_nonce.cpp" // compute_nonce
#include "lib/formatted.cpp" // Formatted
#include <map>               // std::map
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

ETrade::OAuthHeader::OAuthHeader(props_t props_) {
  if (props_.params["oauth_consumer_key"].empty()) {
    std::string error_message =
        Formatted::error_message("`oauth_consumer_key` must be provided");

    throw std::invalid_argument(error_message);
  }

  if (props_.params["oauth_consumer_secret"].empty()) {
    std::string error_message =
        Formatted::error_message("`oauth_consumer_secret` must be provided");

    throw std::invalid_argument(error_message);
  }

  props_.params =
      utils::map::merge(props_.params, {{"oauth_callback", "oob"},
                                        {"oauth_signature_method", "HMAC-SHA1"},
                                        {"oauth_version", "1.0"}});

  props = props_;
}

#endif
