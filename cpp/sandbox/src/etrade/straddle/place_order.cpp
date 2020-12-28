#if !defined ETRADE__STRADDLE_place_order
#define ETRADE__STRADDLE_place_order

#include "build_place_order_payload.cpp"   // build_place_order_payload
#include "handle_request_error.cpp"        // handle_request_error
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "preview_order.cpp"               // preview_order
#include "straddle.h" // ETrade::Straddle, etrade_client, order_t

CurlClient ETrade::Straddle::place_order(order_t order) {
  Formatted::fmt_stream_t fmt = stream_format;

  std::string request_url =
      etrade_client.client_config.base_url + "/accounts/" +
      etrade_client.client_config.account_id_key + "/orders/place.json";

  CurlClient preview_curl_client = preview_order(order);

  std::string payload =
      build_place_order_payload(preview_curl_client.response.body);

  CurlClient curl_client = etrade_client.post({
      .body = payload,
      .method = CurlClient::http_method_t::POST,
      .url = request_url,
  });

  return handle_request_error(curl_client, order.action, "Place");
}

#endif
