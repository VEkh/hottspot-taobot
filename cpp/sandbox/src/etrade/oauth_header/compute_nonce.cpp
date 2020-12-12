#if !defined ETRADE__OAUTH_HEADER_compute_nonce
#define ETRADE__OAUTH_HEADER_compute_nonce

#include "etrade/deps.cpp" // SHA1, SHA_DIGEST_LENGTH
#include "oauth_header.h"  // ETrade::OAuthHeader, timestamp
#include <iomanip>         // std::hex, std::setfill, std::setw
#include <sstream>         // std::stringstream
#include <string>          // std::to_string

std::string to_hex_string(unsigned char *input) {
  int length = strlen((char *)input);

  std::stringstream ss;
  ss << std::hex << std::setw(2) << std::setfill('0');

  for (int i = 0; i < length; ++i) {
    ss << (unsigned int)input[i];
  }

  return ss.str();
}

std::string ETrade::OAuthHeader::compute_nonce() {
  const unsigned char *timestamp_str =
      (unsigned char *)std::to_string(timestamp).c_str();

  unsigned char output[SHA_DIGEST_LENGTH];

  SHA1(timestamp_str, strlen((char *)timestamp_str), output);

  return to_hex_string(output);
}

#endif
