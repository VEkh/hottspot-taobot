/* Dependencies:
 * libcurl4-openssl-dev
 * openssl
 */

#include "deps/cpp-base64/base64.cpp" // base64_encode
#include <ctime>                      // std::time
#include <curl/curl.h>                // curl_easy_escape, curl_easy_init
#include <iomanip>                    // std::hex, std::setfill, std::setw
#include <iostream>                   // std::stringstream
#include <map>                        // std::map
#include <openssl/evp.h>              // EVP_MAX_MD_SIZE, EVP_MD
#include <openssl/hmac.h>             // HMAC
#include <openssl/sha.h>              // SHA1
#include <sstream>                    // std::stringstream
#include <stdexcept>                  // std::invalid_argument
#include <stdlib.h>                   // getenv, rand, srand
#include <string.h>                   // strlen
#include <string>                     // std::string, std::to_string

std::map<const char *, const char *> OAUTH = {
    {"CALLBACK", "oob"}, {"SIGNATURE_METHOD", "HMAC-SHA1"}, {"VERSION", "1.0"}};

std::string toHexString(unsigned char *input) {
  int length = strlen((char *)input);

  std::stringstream ss;
  ss << std::hex << std::setw(2) << std::setfill('0');

  for (int i = 0; i < length; ++i) {
    ss << (unsigned int)input[i];
  }

  return ss.str();
}

std::string percentDecode(const char *str) {
  if (str == NULL) {
    return "";
  }

  CURL *curl = curl_easy_init();
  int output_length;
  const char *unescaped =
      curl_easy_unescape(curl, str, strlen(str), &output_length);

  std::cout << unescaped << std::endl;

  return (std::string)unescaped;
}

std::string percentEncode(const char *str) {
  if (str == NULL) {
    return "";
  }

  CURL *curl = curl_easy_init();
  const char *escaped = curl_easy_escape(curl, str, strlen(str));

  return (std::string)escaped;
}

std::string percentEncode(std::string str) {
  return percentEncode(str.c_str());
}

std::string computeNonce(std::time_t timestamp) {
  const unsigned char *timestamp_str =
      (unsigned char *)std::to_string(timestamp).c_str();

  unsigned char output[SHA_DIGEST_LENGTH];

  SHA1(timestamp_str, strlen((char *)timestamp_str), output);

  return toHexString(output);
}

std::string buildSignatureBaseString(std::time_t timestamp) {
  const char *query_uri = "https://apisb.etrade.com/oauth/request_token";

  std::stringstream params;
  std::stringstream signature_base_string;

  params << "oauth_callback=" << percentEncode(OAUTH["CALLBACK"])
         << "&oauth_consumer_key=" << percentEncode(OAUTH["CONSUMER_KEY"])
         << "&oauth_nonce=" << percentEncode(computeNonce(timestamp))
         << "&oauth_signature_method="
         << percentEncode(OAUTH["SIGNATURE_METHOD"])
         << "&oauth_timestamp=" << timestamp;

  signature_base_string << "GET"
                        << "&" << percentEncode(query_uri) << "&"
                        << percentEncode(params.str());

  return signature_base_string.str();
}

std::string buildOauthSignature(time_t timestamp) {
  std::stringstream key_stream;

  key_stream << OAUTH["CONSUMER_SECRET"] << "&" << OAUTH["OAUTH_TOKEN_SECRET"];
  std::string key = key_stream.str();

  const std::string data = buildSignatureBaseString(timestamp);

  unsigned char output[EVP_MAX_MD_SIZE];
  unsigned int output_length;

  HMAC(EVP_sha1(), key.c_str(), key.length(), (unsigned char *)data.c_str(),
       data.length(), output, &output_length);

  std::stringstream output_stream;
  for (int i = 0; i < output_length; i++) {
    output_stream << output[i];
  }

  std::string signature = base64_encode(output_stream.str());

  return signature;
}

void setSecretCredentials() {
  char *consumer_key = std::getenv("CONSUMER_KEY");

  if (consumer_key == NULL) {
    throw std::invalid_argument("CONSUMER_KEY must be provided");
  }

  char *consumer_secret = std::getenv("CONSUMER_SECRET");

  if (consumer_secret == NULL) {
    throw std::invalid_argument("CONSUMER_SECRET must be provided");
  }

  OAUTH["CONSUMER_KEY"] = consumer_key;
  OAUTH["CONSUMER_SECRET"] = consumer_secret;
}

int main() {
  setSecretCredentials();
  std::time_t timestamp = std::time(nullptr);
  std::string signature = buildOauthSignature(timestamp);

  std::stringstream header;

  header << "Authorization: OAuth realm=\"\","
         << "oauth_callback=\"" << OAUTH["CALLBACK"] << "\","
         << "oauth_consumer_key=\"" << OAUTH["CONSUMER_KEY"] << "\","
         << "oauth_nonce=\"" << percentEncode(computeNonce(timestamp)) << "\","
         << "oauth_signature=\"" << percentEncode(signature) << "\","
         << "oauth_signature_method=\"" << OAUTH["SIGNATURE_METHOD"] << "\","
         << "oauth_timestamp=\"" << timestamp << "\"";

  std::cout << header.str() << std::endl;

  return 0;
}
