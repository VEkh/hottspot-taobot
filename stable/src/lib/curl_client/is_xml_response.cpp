#if !defined CURL_CLIENT_is_xml_response
#define CURL_CLIENT_is_xml_response

#include "curl_client.h" // CurlClient
#include <regex>         // std::regex, std::regex_search

bool CurlClient::is_xml_response() {
  return std::regex_search(response.headers["Content-Type"],
                           std::regex("text\\/html"));
}

#endif
