#include "src/utils/debugger.cpp" // utils::debugger::inspect
#include <cstring>                // std::string
#include <sstream>                // std::stringstream
#include <string>                 // std::string

/*
 * CURL
 * CURLCode
 * CURLOPT_HTTPHEADER
 * CURLOPT_URL
 * CURLOPT_WRITEFUNCTION
 * curl_easy_init
 * curl_easy_perform
 * curl_easy_setopt
 * curl_slist
 * curl_slist_append
 */
#include <curl/curl.h>

size_t write_response(char *buffer, size_t size, size_t nmemb, void *userdata) {
  std::stringstream response;

  response << buffer;

  utils::debugger::inspect(response.str());

  return size * nmemb;
}

int main() {
  std::cout << std::filesystem::current_path() << std::endl;
  CURL *curl = curl_easy_init();
  curl_slist *headers = NULL;
  curl_easy_setopt(curl, CURLOPT_URL,
                   "https://api.tdameritrade.com/v1/oauth2/token");

  // headers = curl_slist_append(headers, "Authorization: Bearer foobarr");
  headers = curl_slist_append(
      headers, "Content-Type: application/x-www-form-urlencoded");

  const char *data = "{'foo': 'bar'}";

  curl_easy_setopt(curl, CURLOPT_POST, 1);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(data));
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
}
