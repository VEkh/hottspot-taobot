#ifndef ETRADE__OAUTH_HEADER_compute_nonce
#define ETRADE__OAUTH_HEADER_compute_nonce

#include "etrade/deps.cpp"    // SHA1, SHA_DIGEST_LENGTH
#include "lib/utils/time.cpp" // utils::time_
#include "oauth_header.h"     // ETrade::OAuthHeader, timestamp
#include <iomanip>            // std::hex, std::setfill, std::setw
#include <sstream>            // std::stringstream
#include <string>             // std::to_string

std::string to_hex_string(unsigned char *input) {
  int length = strlen((char *)input);

  std::stringstream ss;
  ss << std::hex << std::setw(2) << std::setfill('0');

  for (int i = 0; i < length; ++i) {
    ss << (unsigned int)input[i];
  }

  return ss.str();
}

std::string ETrade::OAuthHeader::compute_nonce(
    std::string key = std::to_string(::utils::time_::epoch("nanoseconds"))) {
  const unsigned char *key_c_string = (unsigned char *)key.c_str();

  unsigned char out[SHA_DIGEST_LENGTH];

  SHA1(key_c_string, strlen((char *)key_c_string), out);

  return to_hex_string(out);
}

#endif
