#if !defined CURL_CLIENT_set_headers
#define CURL_CLIENT_set_headers

#include "curl_client.h"        // CurlClient, curl, props, transformed_props
#include "lib/utils/vector.cpp" // utils::vector::join
#include <map>                  // std::map
#include <string>               // std::string
#include <vector>               // std::vector

/*
 * CURLOPT_HTTPHEADER
 * curl_easy_setopt
 * curl_slist
 * curl_slist_append
 */
#include <curl/curl.h>

void CurlClient::set_headers() {
  curl_slist *request_headers = NULL;
  std::map<std::string, std::string> headers = props.headers;
  std::map<std::string, std::string>::iterator it;
  std::vector<std::string> header_pairs;

  for (it = headers.begin(); it != headers.end(); it++) {
    std::string header = (it->first + ": " + it->second);

    header_pairs.push_back("-H '" + header + "'");
    request_headers = curl_slist_append(request_headers, header.c_str());
  }

  transformed_props.headers = utils::vector::join(header_pairs, " ");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, request_headers);
}

#endif
