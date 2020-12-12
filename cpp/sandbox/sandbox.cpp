#include "lib/utils/debug.cpp"  // utils::debug
#include "lib/utils/string.cpp" // utils::string
#include <iostream>             // std::cout, std::endl
#include <map>                  // std::map
#include <regex>                // std::regex, std::regex_constants, std::smatch
#include <vector>               // std::vector

std::vector<std::string> extract_header_parts(const char *header) {
  std::regex key_value_regex("(.*):\\s(.*)\\s?$");
  std::cmatch match;

  std::regex_search(header, match, key_value_regex);

  if (match.size() == 3) {
    return {std::string(match[1]), std::string(match[2])};
  }

  std::regex status_regex(".*http\\/\\d\\.\\d\\s(\\d+).*",
                          std::regex_constants::icase);

  std::regex_search(header, match, status_regex);

  if (match.size() == 2) {
    return {"Status", std::string(match[1])};
  }

  return {};
}

int main() {
  std::vector<const char *> response_headers = {
      "HTTP/1.1 200 OK",
      "Date: Sat, 12 Dec 2020 21:07:10 GMT\n",
      "Server: Apache\n",
      "Set-Cookie: JSESSIONID=2827667600C9E4814B03DD161B9BAE7C.tomcat2;"
      "Path=/oauth; Secure; HttpOnly\n",
      "Transfer-Encoding: chunked\n",
      "Content-Type: application/x-www-form-urlencoded;charset=ISO-8859-1\n",
  };

  std::map<std::string, std::string> headers;

  for (int i = 0; i < response_headers.size(); i++) {
    std::vector<std::string> parts = extract_header_parts(response_headers[i]);

    if (parts.size() > 1) {
      headers[parts[0]] = parts[1];
    }
  }

  utils::debug::inspect(headers);
}
