#include "deps/cpp-base64/base64.cpp"
#include <algorithm>   // std::transform
#include <curl/curl.h> // curl_easy_escape, curl_easy_init
#include <cxxabi.h>
#include <iomanip>
#include <iostream>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <sstream>
#include <string.h>

std::string uriEscape(const char *str) {
  if (str == NULL) {
    return "";
  }

  CURL *curl = curl_easy_init();
  const char *escaped = curl_easy_escape(curl, str, strlen(str));

  return (std::string)escaped;
}

int main() {
  const char *key = "59a8ce75cf8bc55992a77f08cf1930b3";
  const char *oauth_token =
      "Uf9qeY%2BPJz6q4GCuSuN%2Bp%2F7sRKpKbwiUTiPDhrW3p%2F8%3D";

  std::stringstream url_stream;
  url_stream << "https://us.etrade.com/e/t/etws/authorize?"
             << "key=" << key << "&token=" << oauth_token;

  std::cout << url_stream.str() << std::endl;
}
