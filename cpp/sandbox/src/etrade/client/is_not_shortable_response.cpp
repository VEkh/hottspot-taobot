#if !defined ETRADE__CLIENT_is_not_shortable_response
#define ETRADE__CLIENT_is_not_shortable_response

#include "client.h"                      // ETrade::Client, stream_format
#include "etrade/deps.cpp"               // json
#include "lib/curl_client/curl_client.h" // CurlClient

bool ETrade::Client::is_not_shortable_response(const CurlClient &curl_client) {
  json response_body = json::parse(curl_client.response.body);

  return response_body.contains("Error") &&
         response_body["Error"]["code"] == 33;
}

#endif
