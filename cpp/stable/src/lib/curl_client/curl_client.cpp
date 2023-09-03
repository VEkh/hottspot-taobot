#ifndef CURL_CLIENT
#define CURL_CLIENT

#include "curl_client.h" // CurlClient, props
#include "is_xml_response.cpp"
#include "method_to_string.cpp"
#include "request.cpp"
#include "set_debug.cpp"        // set_debug
#include "set_headers.cpp"      // set_headers
#include "set_method.cpp"       // set_method
#include "set_request_body.cpp" // set_request_body
#include "set_url.cpp"          // set_url

CurlClient::CurlClient(props_t props_) {
  props = props_;
  prepare_request();
}

void CurlClient::prepare_request() {
  set_request_body();
  set_debug();
  set_headers();
  set_method();
  set_url();
}

#endif
