#if !defined ETRADE__OAUTH_HEADER_build_signature
#define ETRADE__OAUTH_HEADER_build_signature

#include "build_signature_base_string.cpp" // build_signature_base_string
#include "etrade/deps.cpp" // base64_encode, EVP_MAX_MD_SIZE, HMAC
#include "oauth_header.h"  // ETrade::OAuthHeader, props
#include <sstream>         // std::stringstream
#include <string>          // std::string

std::string ETrade::OAuthHeader::build_signature() {
  std::string key = props.params["oauth_consumer_secret"] + "&" +
                    props.params["oauth_token_secret"];

  const std::string data = build_signature_base_string();

  unsigned char output[EVP_MAX_MD_SIZE];
  unsigned int output_length;

  HMAC(EVP_sha1(), key.c_str(), key.length(), (unsigned char *)data.c_str(),
       data.length(), output, &output_length);

  std::stringstream output_stream;
  for (int i = 0; i < output_length; i++) {
    output_stream << output[i];
  }

  return base64_encode(output_stream.str());
}

#endif
