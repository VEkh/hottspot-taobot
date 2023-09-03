#if !defined CURL_CLIENT_set_debug
#define CURL_CLIENT_set_debug

#include "curl_client.h" // CurlClient, curl, props
#include <curl/curl.h>   // CURLOPT_VERBOSE, curl_easy_setopt

void CurlClient::set_debug() {
  curl_easy_setopt(curl, CURLOPT_VERBOSE, (long)props.debug_flag);
}

#endif
