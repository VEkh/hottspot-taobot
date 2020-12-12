#if !defined ETRADE__OAUTH_HEADER_build
#define ETRADE__OAUTH_HEADER_build

#include "build_signature.cpp" // build_signature
#include "oauth_header.h"      // ETrade::OAuthHeader
#include <sstream>             // std::stringstream
#include <string>              // std::string

std::string ETrade::OAuthHeader::build() {
  std::string signature = build_signature();

  std::stringstream header;
  header << "OAuth realm=\"\","
         << "oauth_callback=\"" << props.params["oauth_callback"] << "\","
         << "oauth_consumer_key=\"" << props.params["oauth_consumer_key"]
         << "\","
         << "oauth_nonce=\"" << nonce << "\","
         << "oauth_signature=\"" << utils::uri::percent_encode(signature)
         << "\","
         << "oauth_signature_method=\""
         << props.params["oauth_signature_method"] << "\","
         << "oauth_timestamp=\"" << timestamp << "\"";

  if (!props.params["oauth_token"].empty()) {
    header << ",oauth_token=\"" << props.params["oauth_token"] << "\"";
  }

  if (!props.params["oauth_verifier"].empty()) {
    header << ",oauth_verifier=\"" << props.params["oauth_verifier"] << "\"";
  }

  return header.str();
}

#endif
