#if !defined ETRADE__STRADDLE_open
#define ETRADE__STRADDLE_open

#include "build_place_order_payload.cpp"   // build_place_order_payload
#include "build_preview_order_payload.cpp" // build_preview_order_payload
#include "etrade/deps.cpp"                 // json
#include "lib/formatted.cpp"               // Formatted
#include "lib/utils/float.cpp"             // utils::float_
#include "lib/utils/string.cpp"            // utils::string
#include <chrono>                          // std::chrono
#include <cmath>                           // pow
#include <iostream>                        // std::cout, std::endl
#include <thread>                          // std::this_thread

/*
 * ETrade::Straddle
 * etrade_client
 * order_status_t
 * order_t
 * stream_format
 */
#include "straddle.h"

CurlClient handle_request_error(CurlClient curl_client, const char *order_type,
                                std::string action) {
  json response_body = json::parse(curl_client.response.body);

  if (response_body.contains(action + "OrderResponse")) {
    return curl_client;
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red;
  std::cout << "❌ Something went wrong while trying to "
            << utils::string::downcase(action) << " the " << order_type
            << " order: " << std::endl;
  std::cout << response_body.dump(2) << std::endl;
  std::cout << fmt.reset;

  exit(1);
}

void update_order(ETrade::Straddle::order_t order, std::string response_body) {
  json response = json::parse(response_body);

  order.id = response["PlaceOrderResponse"]["OrderIds"][0]["orderId"];
  order.status = ETrade::Straddle::order_status_t::ORDER_OPEN;
}

void ETrade::Straddle::open() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::string preview_order_url = "https://api.etrade.com/v1/accounts/" +
                                  etrade_client.client_config.account_id_key +
                                  "/orders/preview.json";

  std::string place_order_url = "https://api.etrade.com/v1/accounts/" +
                                etrade_client.client_config.account_id_key +
                                "/orders/place.json";

  std::string preview_buy_payload = build_preview_order_payload(buy_open_order);

  std::string preview_sell_short_payload =
      build_preview_order_payload(sell_short_open_order);

  CurlClient preview_buy_curl_client = etrade_client.post({
      .body = preview_buy_payload,
      .method = CurlClient::http_method_t::POST,
      .url = preview_order_url,
  });

  CurlClient preview_sell_short_curl_client = etrade_client.post({
      .body = preview_sell_short_payload,
      .method = CurlClient::http_method_t::POST,
      .url = preview_order_url,
  });

  handle_request_error(preview_buy_curl_client, "BUY", "Preview");
  handle_request_error(preview_sell_short_curl_client, "SELL_SHORT", "Preview");

  std::string place_buy_payload =
      build_place_order_payload(preview_buy_curl_client.response.body);

  std::string place_sell_short_payload =
      build_place_order_payload(preview_sell_short_curl_client.response.body);

  CurlClient place_sell_short_curl_client = etrade_client.post({
      .body = place_sell_short_payload,
      .method = CurlClient::http_method_t::POST,
      .url = place_order_url,
  });

  CurlClient place_buy_curl_client = etrade_client.post({
      .body = place_buy_payload,
      .method = CurlClient::http_method_t::POST,
      .url = place_order_url,
  });

  update_order(buy_open_order, place_buy_curl_client.response.body);
  update_order(sell_short_open_order,
               place_sell_short_curl_client.response.body);

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "✅ Straddle successfully opened!" << std::endl;
  std::cout << fmt.reset;
}

#endif
