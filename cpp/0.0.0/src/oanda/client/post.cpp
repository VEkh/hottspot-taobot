#ifndef OANDA__CLIENT_post
#define OANDA__CLIENT_post

/*
 * Oanda::Client
 * post_params_t
 */
#include "client.h"

#include "lib/curl_client/curl_client.cpp" // CurlClient
#include <string>                          // std::string

CurlClient Oanda::Client::post(const post_params_t params) {
  CurlClient curl_client = CurlClient({
      .body = params.body,
      .body_params = {},
      .debug_flag = CurlClient::debug_t::OFF,
      .headers =
          {
              {"Authorization",
               std::string("Bearer ") + this->config.authentication_token},
              {"Content-Type", "application/json"},
          },
      .method = params.method,
      .query_params = {},
      .url = params.url,
  });

  curl_client.request();

  return curl_client;
}

#endif
