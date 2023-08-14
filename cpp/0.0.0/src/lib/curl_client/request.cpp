#ifndef CURL_CLIENT_request
#define CURL_CLIENT_request

/*
 * CurlClient
 * curl
 * debug_t
 * props
 * response
 */
#include "curl_client.h"

#include "log_request.cpp"            // log_request
#include "write_response_body.cpp"    // write_response_body
#include "write_response_headers.cpp" // write_response_headers

/*
 * CURLOPT_HEADERDATA
 * CURLOPT_HEADERFUNCTION
 * CURLOPT_WRITEDATA
 * CURLOPT_WRITEFUNCTION
 * curl_easy_cleanup
 * curl_easy_perform
 * curl_easy_setopt
 */
#include <curl/curl.h>

void CurlClient::request() {
  if (props.debug_flag == debug_t::ON) {
    log_request();
  }

  curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&response);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_response_headers);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response_body);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
}

#endif
