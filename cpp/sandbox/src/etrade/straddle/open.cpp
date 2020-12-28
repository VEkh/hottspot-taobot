#if !defined ETRADE__STRADDLE_open
#define ETRADE__STRADDLE_open

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include "place_order.cpp"   // place_order
#include "straddle.h"        // ETrade::Straddle, stream_format
#include <iostream>          // std::cout, std::endl

void update_order(ETrade::Straddle::order_t order, std::string response_body) {
  json response = json::parse(response_body);

  order.id = response["PlaceOrderResponse"]["OrderIds"][0]["orderId"];
  order.status = ETrade::Straddle::order_status_t::ORDER_OPEN;
}

void ETrade::Straddle::open() {
  Formatted::fmt_stream_t fmt = stream_format;

  CurlClient place_sell_short_curl_client = place_order(sell_short_open_order);
  CurlClient place_buy_curl_client = place_order(buy_open_order);

  update_order(buy_open_order, place_buy_curl_client.response.body);
  update_order(sell_short_open_order,
               place_sell_short_curl_client.response.body);

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "✅ Straddle successfully opened!" << std::endl;
  std::cout << fmt.reset;
}

#endif
