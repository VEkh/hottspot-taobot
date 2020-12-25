#if !defined ETRADE__STRADDLE_build_preview_order_payload
#define ETRADE__STRADDLE_build_preview_order_payload

#include "compute_client_order_id.cpp" // compute_client_order_id
#include "etrade/deps.cpp"             // json, _json
#include "lib/utils/float.cpp"         // utils::float_
#include "straddle.h" // ETrade::Straddle, prices_t, quantity, symbol
#include <string>     // std::string

std::string
ETrade::Straddle::build_preview_order_payload(const char *order_type,
                                              prices_t prices) {
  json payload = R"(
    {
      "PreviewOrderRequest":{
        "orderType":"EQ",
        "clientOrderId":"abcd1234",
        "Order":[]
      }
    }
  )"_json;

  json order = R"(
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
      "priceType":"STOP_LIMIT",
      "stopPrice":444.40
    }
  )"_json;

  order["Instrument"][0]["Product"]["symbol"] = symbol;
  order["Instrument"][0]["orderAction"] = order_type;
  order["Instrument"][0]["quantity"] = quantity;
  order["limitPrice"] = utils::float_::to_currency(prices.open_stop_limit);
  order["stopPrice"] = utils::float_::to_currency(prices.open_stop);

  payload["PreviewOrderRequest"]["Order"].push_back(order);
  payload["PreviewOrderRequest"]["clientOrderId"] = compute_client_order_id();

  return payload.dump();
}

#endif
