/* Dependencies:
 * libcurl4-openssl-dev
 */

#include <curl/curl.h> // curl_easy_escape, curl_easy_init
#include <iostream>    // std::stringstream
#include <string.h>    // strlen
#include <string>      // std::string

std::string percentDecode(const char *str) {
  if (str == NULL) {
    return "";
  }

  CURL *curl = curl_easy_init();
  int output_length;
  const char *unescaped =
      curl_easy_unescape(curl, str, strlen(str), &output_length);

  return (std::string)unescaped;
}

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    std::cout << percentDecode(argv[i]) << std::endl;
  }

  return 0;
}
