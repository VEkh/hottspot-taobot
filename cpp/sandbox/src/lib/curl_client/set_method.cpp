#ifndef CURL_CLIENT_set_method
#define CURL_CLIENT_set_method

#include "lib/utils/vector.cpp" // utils::vector::join
#include <map>                  // std::map
#include <string>               // std::string
#include <vector>               // std::vector

/*
 * CurlClient
 * curl
 * http_method_t
 * props
 * transformed_props
 */
#include "curl_client.h"

/*
 * CURLOPT_HTTPGET
 * CURLOPT_POST
 * curl_easy_setopt
 */
#include <curl/curl.h>

void CurlClient::set_method() {
  switch (props.method) {
  case http_method_t::DELETE: {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    break;
  }
  case http_method_t::GET: {
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    break;
  }
  case http_method_t::POST: {
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    break;
  }
  case http_method_t::PUT: {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    break;
  }
  }

  transformed_props.method = method_to_string(props.method);
}

#endif
