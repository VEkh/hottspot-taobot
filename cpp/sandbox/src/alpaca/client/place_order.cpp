#ifndef ALPACA__CLIENT_place_order
#define ALPACA__CLIENT_place_order

/*
 * Alpaca::Client
 * fmt
 * order_action_t
 * order_status_t
 * order_t
 */
#include "client.h"

#include "alpaca/constants.cpp"                   // Alpaca::constants
#include "deps.cpp"                               // json, _json
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/utils/float.cpp"                    // ::utils::float_
#include "lib/utils/json.cpp"                     // ::utils::json
#include "post.cpp"                               // post
#include <ctime>                                  // std::time, std::time_t
#include <iostream>                               // std::cout, std::endl
#include <regex>     // std::regex, std::regex_search
#include <stdexcept> // std::invalid_argument
#include <string>    // std::stod
#include <unistd.h>  // usleep

namespace Alpaca {
namespace place_order {
bool is_immediate_retry_error(const CurlClient &curl_client) {
  const Formatted::fmt_stream_t fmt = Formatted::stream();
  const std::string response_body = curl_client.response.body;

  if (response_body.empty()) {
    return true;
  }

  if (std::regex_search(response_body, std::regex("rate limit exceeded"))) {
    std::cout << fmt.bold << fmt.yellow;
    puts("[ALPACA__CLIENT_place_order] Rate limit exceeded.");
    std::cout << fmt.reset << std::endl;

    return true;
  };

  return false;
}
} // namespace place_order
} // namespace Alpaca

CurlClient Alpaca::Client::place_order(order_t *order) {
  std::string url = this->config.base_url + "/v2/orders";

  json body = R"(
    {
      "qty": 1.000000000,
      "side": "BUY|SELL",
      "symbol": "XXXX",
      "time_in_force": "day",
      "type": "MARKET"
    }
  )"_json;

  body["qty"] = order->quantity;
  body["side"] = Alpaca::constants::ORDER_ACTIONS[order->action];
  body["symbol"] = order->symbol;
  body["time_in_force"] =
      Alpaca::constants::ORDER_TIMES_IN_FORCE[order->time_in_force];
  body["type"] = Alpaca::constants::ORDER_TYPES[order->type];

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return post({
            .body = body.dump(),
            .method = CurlClient::http_method_t::POST,
            .url = url,
        });
      },
      Alpaca::place_order::is_immediate_retry_error);

  json response = ::utils::json::parse_with_catch(curl_client.response.body,
                                                  "ALPACA__CLIENT_place_order");

  std::cout << fmt.yellow << fmt.bold;
  printf("Order response: %s\n", response.dump(2).c_str());
  std::cout << fmt.reset;
  std::cout << std::flush;

  if (!response.contains("id")) {
    std::cout << fmt.red << fmt.bold;
    printf("❌ Failed to place order. Here's the response: %s\n",
           response.dump(2).c_str());
    std::cout << std::endl;

    return curl_client;
  }

  std::time_t now = std::time(nullptr);

  order->id = response["id"];
  order->status = order_status_t::ORDER_NEW;
  order->timestamp = now;

  return curl_client;
}

#endif
