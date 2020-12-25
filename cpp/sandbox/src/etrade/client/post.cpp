#if !defined ETRADE__CLIENT_post
#define ETRADE__CLIENT_post

#include "build_request_header.cpp"        // build_request_header
#include "client.h"                        // ETrade::Client, oauth
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "load_token.cpp"                  // load_token
#include <string>                          //  std::string

CurlClient ETrade::Client::post(std::string url, std::string body) {
  load_token();

  std::string request_header = build_request_header({
      .method = CurlClient::http_method_t::POST,
      .params =
          {
              {"oauth_token", oauth.token},
              {"oauth_token_secret", oauth.token_secret},
          },
      .request_url = url,
  });

  CurlClient curl_client = CurlClient({
      .body = body,
      .body_params = {},
      .debug_flag = (CurlClient::debug_t)props.debug_flag,
      .headers =
          {
              {"Authorization", request_header},
              {"Content-Type", "application/json"},
          },
      .method = CurlClient::http_method_t::POST,
      .query_params = {},
      .url = url,
  });

  curl_client.request();

  return curl_client;
}

#endif
