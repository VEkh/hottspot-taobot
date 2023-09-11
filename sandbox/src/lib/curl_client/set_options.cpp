#ifndef CURL_CLIENT_set_options
#define CURL_CLIENT_set_options

#include "curl_client.h" // CurlClient
#include <curl/curl.h>   // curl_easy_setopt, CURLOPT_TIMEOUT

void CurlClient::set_options() {
  curl_easy_setopt(this->curl, CURLOPT_TIMEOUT, this->props.timeout_seconds);
}

#endif
