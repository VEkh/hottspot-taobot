#if !defined ETRADE__STRADDLE_build_place_order_payload
#define ETRADE__STRADDLE_build_place_order_payload

#include "compute_client_order_id.cpp" // compute_client_order_id
#include "etrade/deps.cpp"             // json
#include "lib/utils/json.cpp"          // utils::json
#include "straddle.h"                  // ETrade::Straddle
#include <string>                      // std::string

std::string
ETrade::Straddle::build_place_order_payload(std::string preview_response) {
  json payload;
  json preview = json::parse(preview_response)["PreviewOrderResponse"];

  payload["PlaceOrderRequest"] =
      utils::json::jslice(preview, {"Order", "PreviewIds", "orderType"});

  payload["PlaceOrderRequest"]["clientOrderId"] =
      compute_client_order_id(payload.dump());

  return payload.dump();
}

#endif
