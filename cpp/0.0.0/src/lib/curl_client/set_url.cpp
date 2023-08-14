#if !defined CURL_CLIENT_set_url
#define CURL_CLIENT_set_url

/*
 * CurlClient
 * curl
 * props
 * transformed_props
 */
#include "curl_client.h"

#include "build_query_params.cpp" // build_query_params
#include "lib/utils/vector.cpp"   // utils::vector::join
#include <curl/curl.h>            // CURLOPT_URL, curl_easy_setopt
#include <stdexcept>              // std::invalid_argument
#include <string>                 // std::string

void CurlClient::set_url() {
  if (props.url.empty()) {
    throw std::invalid_argument(
        "You must provide a target URL (e.g. https://example.com)");
  }

  std::string url = props.url + build_query_params();

  transformed_props.url = url;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
}

#endif
