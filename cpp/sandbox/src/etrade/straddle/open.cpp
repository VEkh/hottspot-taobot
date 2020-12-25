#if !defined ETRADE__STRADDLE_open
#define ETRADE__STRADDLE_open

#include "build_place_order_payload.cpp"   // build_place_order_payload
#include "build_preview_order_payload.cpp" // build_preview_order_payload
#include "etrade/deps.cpp"                 // json
#include "lib/formatted.cpp"               // Formatted
#include "lib/utils/float.cpp"             // utils::float_
#include "lib/utils/string.cpp"            // utils::string
#include "straddle.h" // ETrade::Straddle, quantity, stream_format, symbol, etrade_client
#include <iostream> // std::cout, std::endl

void handle_request_error(CurlClient curl_client, const char *order_type,
                          std::string action) {
  json preview_response = json::parse(curl_client.response.body);

  if (preview_response.contains(action + "OrderResponse")) {
    return;
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red;
  std::cout << "❌ Something went wrong while "
            << utils::string::downcase(action) << "ing the " << order_type
            << " order: " << std::endl;
  std::cout << preview_response.dump(2) << std::endl;
  std::cout << fmt.reset;

  exit(1);
}

int extract_order_id(std::string response_body) {
  json response = json::parse(response_body);
  return response["PlaceOrderResponse"]["OrderIds"][0]["orderId"];
}

void ETrade::Straddle::open() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::string preview_order_url = "https://api.etrade.com/v1/accounts/" +
                                  etrade_client.client_config.account_id_key +
                                  "/orders/preview.json";

  std::string place_order_url = "https://api.etrade.com/v1/accounts/" +
                                etrade_client.client_config.account_id_key +
                                "/orders/place.json";

  std::string preview_buy_payload =
      build_preview_order_payload("BUY", order_prices.buy);

  std::string preview_sell_short_payload =
      build_preview_order_payload("SELL_SHORT", order_prices.sell_short);

  CurlClient preview_buy_curl_client =
      etrade_client.post(preview_order_url, preview_buy_payload);

  CurlClient preview_sell_short_curl_client =
      etrade_client.post(preview_order_url, preview_sell_short_payload);

  handle_request_error(preview_buy_curl_client, "BUY", "Preview");
  handle_request_error(preview_sell_short_curl_client, "SELL_SHORT", "Preview");

  std::string place_buy_payload =
      build_place_order_payload(preview_buy_curl_client.response.body);

  std::string place_sell_short_payload =
      build_place_order_payload(preview_sell_short_curl_client.response.body);

  CurlClient place_sell_short_curl_client =
      etrade_client.post(place_order_url, place_sell_short_payload);

  CurlClient place_buy_curl_client =
      etrade_client.post(place_order_url, place_buy_payload);

  handle_request_error(place_buy_curl_client, "BUY", "Place");
  handle_request_error(place_sell_short_curl_client, "SELL_SHORT", "Place");

  buy_position_order_ids.open_order_id =
      extract_order_id(place_buy_curl_client.response.body);
  sell_short_position_order_ids.open_order_id =
      extract_order_id(place_sell_short_curl_client.response.body);

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "✅ Straddle successfully opened!" << std::endl;

  std::cout << "Place Buy Response: " << place_buy_curl_client.response.body
            << std::endl;

  std::cout << "Place Sell Short Response: "
            << place_sell_short_curl_client.response.body << std::endl;

  std::cout << fmt.reset;
}

#endif
