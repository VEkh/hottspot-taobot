#if !defined ETRADE__OAUTH_HEADER_build
#define ETRADE__OAUTH_HEADER_build

#include "build_signature.cpp" // build_signature
#include "oauth_header.h"      // ETrade::OAuthHeader,, timestamp timestamp
#include <map>                 // std::map
#include <sstream>             // std::stringstream
#include <string>              // std::string, std::to_string

std::string ETrade::OAuthHeader::build() {
  params = {
      {"oauth_callback", props.params["oauth_callback"]},
      {"oauth_consumer_key", props.params["oauth_consumer_key"]},
      {"oauth_nonce", nonce},
      {"oauth_signature_method", props.params["oauth_signature_method"]},
      {"oauth_timestamp", std::to_string(timestamp)},
      {"oauth_token", props.params["oauth_token"]},
      {"oauth_verifier", props.params["oauth_verifier"]},
  };

  std::string signature = build_signature();
  params["oauth_signature"] = utils::uri::percent_encode(signature);

  std::stringstream header;
  std::map<std::string, std::string>::iterator it;

  header << "OAuth realm=\"\"";

  for (it = params.begin(); it != params.end(); it++) {
    if ((it->second).empty()) {
      continue;
    }

    header << "," << it->first << "=\"" << it->second << "\"";
  }

  return header.str();
}

#endif
