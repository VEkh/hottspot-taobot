#ifndef ALPACA__CLIENT_post
#define ALPACA__CLIENT_post

/*
 * Alpaca::Client
 * post_params_t
 */
#include "client.h"

#include "lib/curl_client/curl_client.cpp" // CurlClient
#include <string>                          // std::string

CurlClient Alpaca::Client::post(const post_params_t params) {
  CurlClient curl_client = CurlClient({
      .body = params.body,
      .body_params = {},
      .debug_flag = CurlClient::debug_t::OFF,
      .headers =
          {
              {"APCA-API-KEY-ID", this->config.api_key_id},
              {"APCA-API-SECRET-KEY", this->config.api_secret_key},
          },
      .method = params.method,
      .query_params = {},
      .timeout_seconds = 0,
      .url = params.url,
  });

  curl_client.request();

  return curl_client;
}

#endif
