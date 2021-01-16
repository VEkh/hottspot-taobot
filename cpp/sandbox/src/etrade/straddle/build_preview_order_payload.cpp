#if !defined ETRADE__STRADDLE_build_preview_order_payload
#define ETRADE__STRADDLE_build_preview_order_payload

#include "compute_client_order_id.cpp" // compute_client_order_id
#include "etrade/deps.cpp"             // json, _json
#include "lib/utils/float.cpp"         // utils::float_
#include <algorithm>                   // std::max, std::min
#include <string>                      // std::string

/*
 * ETrade::Straddle
 * ORDER_ACTIONS
 * ORDER_TYPES
 * order_t
 * quantity
 * quote
 * symbol
 */
#include "straddle.h"

std::string
ETrade::Straddle::build_preview_order_payload(const order_t &order) {
  json payload = R"(
    {
      "PreviewOrderRequest":{
        "orderType":"EQ",
        "clientOrderId":"abcd1234",
        "Order":[]
      }
    }
  )"_json;

  json order_json = R"(
    {
      "Instrument":[
        {
          "Product":{
            "securityType":"EQ",
            "symbol":"TSLA"
          },
          "orderAction":"BUY",
          "quantityType":"QUANTITY",
          "quantity":1
        }
      ],
      "allOrNone":"false",
      "limitPrice":444.44,
      "marketSession":"REGULAR",
      "orderTerm":"GOOD_FOR_DAY",
      "priceType":"STOP_LIMIT"
    }
  )"_json;

  order_json["Instrument"][0]["Product"]["symbol"] = symbol;
  order_json["Instrument"][0]["orderAction"] = ORDER_ACTIONS[order.action];
  order_json["Instrument"][0]["quantity"] = quantity;
  order_json["limitPrice"] = utils::float_::to_currency(order.limit_price);
  order_json["priceType"] = ORDER_TYPES[order.type];

  payload["PreviewOrderRequest"]["Order"].push_back(order_json);

  payload["PreviewOrderRequest"]["clientOrderId"] =
      compute_client_order_id(payload.dump());

  return payload.dump();
}

#endif
