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
#include "oanda/constants.cpp"             // Oanda::constants
#include "post.cpp"                        // post
#include <string>                          // std::stod
#include <time.h>                          // time, time_t

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
  body["order"]["type"] = Oanda::constants::ORDER_TYPES[order->type];
  body["order"]["units"] = quantity_sign * order->quantity;

  CurlClient curl_client = post({
      .body = body.dump(),
      .method = CurlClient::http_method_t::POST,
      .url = url,
  });

  time_t now;
  time(&now);

  json response = json::parse(curl_client.response.body);
  std::string execution_price_string =
      response["orderFillTransaction"]["tradeOpened"]["price"];
  std::string order_id_string = response["orderFillTransaction"]["orderID"];

  order->execution_price = (double)std::stod(execution_price_string);
  order->id = (int)std::stod(order_id_string);
  order->status = order_status_t::ORDER_PENDING;
  order->timestamp = now;

  std::string trade_id_string = "0";

  if (response["orderFillTransaction"].contains("tradeOpened")) {
    trade_id_string =
        response["orderFillTransaction"]["tradeOpened"]["tradeID"];
  } else if (response["orderFillTransaction"].contains("tradesClosed")) {
    trade_id_string =
        response["orderFillTransaction"]["tradesClosed"][0]["tradeID"];
  }

  order->trade_id = (int)std::stod(trade_id_string);

  return curl_client;
}

#endif
