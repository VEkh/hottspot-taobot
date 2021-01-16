#if !defined ETRADE__CLIENT_build_place_order_payload
#define ETRADE__CLIENT_build_place_order_payload

#include "client.h"                    // ETrade::Client
#include "compute_client_order_id.cpp" // compute_client_order_id
#include "etrade/deps.cpp"             // json
#include "lib/utils/json.cpp"          // utils::json
#include <string>                      // std::string

std::string
ETrade::Client::build_place_order_payload(std::string &preview_response) {
  json payload;
  json preview = json::parse(preview_response)["PreviewOrderResponse"];

  payload["PlaceOrderRequest"] =
      utils::json::jslice(preview, {"Order", "PreviewIds", "orderType"});

  payload["PlaceOrderRequest"]["clientOrderId"] =
      compute_client_order_id(payload.dump());

  return payload.dump();
}

#endif
