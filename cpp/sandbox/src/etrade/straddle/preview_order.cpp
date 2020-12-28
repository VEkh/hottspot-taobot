#if !defined ETRADE__STRADDLE_preview_order
#define ETRADE__STRADDLE_preview_order

#include "build_preview_order_payload.cpp" // build_preview_order_payload
#include "handle_request_error.cpp"        // handle_request_error
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "straddle.h" // ETrade::Straddle, etrade_client, order_t

CurlClient ETrade::Straddle::preview_order(order_t order) {
  std::string request_url =
      etrade_client.client_config.base_url + "/accounts/" +
      etrade_client.client_config.account_id_key + "/orders/preview.json";

  std::string payload = build_preview_order_payload(order);

  CurlClient curl_client = etrade_client.post({
      .body = payload,
      .method = CurlClient::http_method_t::POST,
      .url = request_url,
  });

  return handle_request_error(curl_client, order.action, "Preview");
}

#endif
