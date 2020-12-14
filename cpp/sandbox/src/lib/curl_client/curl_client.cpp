#if !defined CURL_CLIENT
#define CURL_CLIENT

#include "curl_client.h" // CurlClient, props
#include "request.cpp"
#include "set_body_params.cpp" // set_body_params
#include "set_debug.cpp"       // set_debug
#include "set_headers.cpp"     // set_headers
#include "set_method.cpp"      // set_method
#include "set_url.cpp"         // set_url

CurlClient::CurlClient(props_t props_) {
  props = props_;
  prepare_request();
}

void CurlClient::prepare_request() {
  set_body_params();
  set_debug();
  set_headers();
  set_method();
  set_url();
}

#endif
