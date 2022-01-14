#ifndef OANDA__CLIENT_place_order
#define OANDA__CLIENT_place_order

/*
 * Oanda::Client
 * order_action_t
 * order_status_t
 * order_t
 */
#include "client.h"

#include "deps.cpp"                        // json, _json
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/utils/float.cpp"             // ::utils::float_
#include "lib/utils/json.cpp"              // ::utils::json
#include "oanda/constants.cpp"             // Oanda::constants
#include "post.cpp"                        // post
#include <ctime>                           // std::time, std::time_t
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::stod

CurlClient Oanda::Client::place_order(order_t *order) {
  std::string url = this->config.base_url + "/v3/accounts/" +
                    this->config.account_id + "/orders";

  int quantity_sign = order->action == order_action_t::SELL ? -1 : 1;

  json body = R"(
    {
      "order": {
        "instrument": "",
        "timeInForce": "FOK",
        "type": "MARKET",
        "units": 1
      }
    }
  )"_json;

  body["order"]["instrument"] = order->symbol;
  body["order"]["timeInForce"] =
      Oanda::constants::ORDER_TIMES_IN_FORCE[order->time_in_force];
  body["order"]["type"] = Oanda::constants::ORDER_TYPES[order->type];
  body["order"]["units"] = quantity_sign * order->quantity;

  CurlClient curl_client = post({
      .body = body.dump(),
      .method = CurlClient::http_method_t::POST,
      .url = url,
  });

  std::time_t now = std::time(nullptr);

  json response = ::utils::json::parse_with_catch(curl_client.response.body,
                                                  "OANDA__CLIENT_place_order");

  std::cout << fmt.yellow << fmt.bold;
  printf("Order payload: %s\n", body.dump(2).c_str());
  std::cout << fmt.reset;

  std::cout << fmt.yellow << fmt.bold;
  printf("Order response: %s\n", response.dump(2).c_str());
  std::cout << fmt.reset;

  if (!response.contains("orderCreateTransaction")) {
    std::string message = Formatted::error_message(
        std::string("❌ Something went wrong while placing the order: ") +
        response.dump(2));

    throw std::runtime_error(message);
  }

  std::string order_id_string = response["orderCreateTransaction"]["id"];

  order->id = (int)std::stod(order_id_string);
  order->status = order_status_t::ORDER_PENDING;
  order->timestamp = now;

  return curl_client;
}

#endif
