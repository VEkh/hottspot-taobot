/* Dependencies:
 * libcurl4-openssl-dev
 * openssl
 */

#include "../deps/cpp-base64/base64.cpp" // base64_encode
#include "utils/debugger.cpp"            // utils::debugger::inspect
#include "utils/string.cpp"              // utils::string::split
#include <any>                           // std::any
#include <ctime>                         // std::time
#include <curl/curl.h>                   // curl_easy_escape, curl_easy_init
#include <iomanip>                       // std::hex, std::setfill, std::setw
#include <iostream>                      // std::stringstream
#include <map>                           // std::map
#include <openssl/evp.h>                 // EVP_MAX_MD_SIZE, EVP_MD
#include <openssl/hmac.h>                // HMAC
#include <openssl/sha.h>                 // SHA1
#include <sstream>                       // std::stringstream
#include <stdexcept>                     // std::invalid_argument
#include <stdlib.h>                      // getenv, rand, srand
#include <string.h>                      // strlen
#include <string>                        // std::string, std::to_string
#include <vector>                        // std::vector

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

std::map<std::string, std::string> parseQueryParams(std::string query_string) {
  if (query_string == "") {
  }

  return (std::map<std::string, std::string>){};
}

std::map<const char *, std::any> parseRequestUrl(std::string request_url) {
  std::map<const char *, std::any> result;
  std::vector<std::string> url_parts = utils::string::split(request_url, "?");

  result["base_url"] = url_parts[0];

  result["query_params"] = parseQueryParams(url_parts[1]);

  return result;
}

std::string buildParamsString(std::time_t timestamp, const char *request_url) {
  std::stringstream output;
  std::map<std::string, std::string> params = {
      {"oauth_callback", percentEncode(OAUTH["CALLBACK"])},
      {"oauth_consumer_key", percentEncode(OAUTH["CONSUMER_KEY"])},
      {"oauth_nonce", computeNonce(timestamp)},
      {"oauth_signature_method", percentEncode(OAUTH["SIGNATURE_METHOD"])},
      {"oauth_timestamp", std::to_string(timestamp)},
      {"oauth_token", OAUTH["TOKEN"] ? OAUTH["TOKEN"] : ""},
      {"oauth_verifier", OAUTH["VERIFER"] ? OAUTH["VERIFER"] : ""}};

  std::map<const char *, std::any> parsed_request_url =
      parseRequestUrl(request_url);

  std::string base_url =
      std::any_cast<std::string>(parsed_request_url["base_url"]);

  std::map<std::string, std::string> query_params =
      std::any_cast<std::map<std::string, std::string>>(
          parsed_request_url["query_params"]);

  utils::debugger::inspect(base_url);
  utils::debugger::inspect(query_params);

  std::map<std::string, std::string>::iterator it;

  for (it = params.begin(); it != params.end(); it++) {
    std::string value = it->second;

    if (value.empty()) {
      continue;
    }

    if (!output.str().empty()) {
      output << "&";
    }

    output << it->first << "=" << value;
  }

  return output.str();
}

std::string buildSignatureBaseString(std::time_t timestamp) {
  const char *request_url = std::getenv("REQUEST_URL");

  std::string params = buildParamsString(timestamp, request_url);
  std::stringstream signature_base_string;

  signature_base_string << "GET"
                        << "&" << percentEncode(request_url) << "&"
                        << percentEncode(params);

  return signature_base_string.str();
}

std::string buildOauthSignature(time_t timestamp) {
  std::stringstream key_stream;

  key_stream << OAUTH["CONSUMER_SECRET"] << "&" << OAUTH["TOKEN_SECRET"];

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
  char *consumer_key = std::getenv("OAUTH_CONSUMER_KEY");
  char *consumer_secret = std::getenv("OAUTH_CONSUMER_SECRET");
  char *token = std::getenv("OAUTH_TOKEN");
  char *token_secret = std::getenv("OAUTH_TOKEN_SECRET");
  char *verfier = std::getenv("OAUTH_VERIFIER");

  if (consumer_key == NULL) {
    throw std::invalid_argument("CONSUMER_KEY must be provided");
  }

  if (consumer_secret == NULL) {
    throw std::invalid_argument("CONSUMER_SECRET must be provided");
  }

  OAUTH["CONSUMER_KEY"] = consumer_key;
  OAUTH["CONSUMER_SECRET"] = consumer_secret;
  OAUTH["TOKEN"] = token;
  OAUTH["TOKEN_SECRET"] = token_secret;
  OAUTH["VERIFER"] = verfier;
}

int main() {
  setSecretCredentials();
  std::time_t timestamp = std::time(nullptr);
  std::string signature = buildOauthSignature(timestamp);

  std::stringstream header;

  header << "Authorization: OAuth realm=\"\","
         << "oauth_callback=\"" << OAUTH["CALLBACK"] << "\","
         << "oauth_consumer_key=\"" << OAUTH["CONSUMER_KEY"] << "\","
         << "oauth_nonce=\"" << computeNonce(timestamp) << "\","
         << "oauth_signature=\"" << percentEncode(signature) << "\","
         << "oauth_signature_method=\"" << OAUTH["SIGNATURE_METHOD"] << "\","
         << "oauth_timestamp=\"" << timestamp << "\"";

  if (OAUTH["TOKEN"]) {
    header << ",oauth_token=\"" << OAUTH["TOKEN"] << "\"";
  }

  if (OAUTH["VERIFER"]) {
    header << ",oauth_verifier=\"" << OAUTH["VERIFER"] << "\"";
  }

  // std::cout << header.str() << std::endl;

  return 0;
}
