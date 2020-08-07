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
  // oauth_token="pFbP03i64OjRzhOPTx/gO1KjwRJI2xE4q7mVe/IpGIw="
  // oauth_token_secret="ZFKfxqtX6lTDRtrzGUdlvx5gMPuSb9qzu8Ea/H1K7sE="

  std::stringstream url_stream;
  url_stream << "https://us.etrade.com/e/t/etws/authorize?"
             << "key=59a8ce75cf8bc55992a77f08cf1930b3"
             << "token=" << uriEscape("tR3+Ty81lMeYAr/Fid0kMTYa/WPvfw==");
}
