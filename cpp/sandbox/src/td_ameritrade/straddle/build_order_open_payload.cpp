#if !defined TD_AMERITRADE__STRADDLE_build_order_open_payload
#define TD_AMERITRADE__STRADDLE_build_order_open_payload

#include "lib/utils/float.cpp" // utils::float_
#include "straddle.h" // TdAmeritrade::Straddle, prices_t, quantity, symbol
#include "td_ameritrade/deps.cpp" // json, _json

json TdAmeritrade::Straddle::build_order_open_payload(const char *order_type,
                                                      prices_t prices) {
  json payload = R"(
    {
      "duration": "DAY",
      "orderLegCollection": [
        {
          "instrument": { "assetType": "EQUITY" },
          "orderLegType": "EQUITY",
          "quantityType": "SHARES"
        }
      ],
      "orderStrategyType": "SINGLE",
      "orderType": "STOP_LIMIT",
      "session": "NORMAL"
    }
  )"_json;

  payload["orderLegCollection"][0]["instruction"] = order_type;
  payload["orderLegCollection"][0]["instrument"]["symbol"] = symbol;
  payload["orderLegCollection"][0]["quantity"] = quantity;
  payload["price"] = utils::float_::round_to(prices.open_stop_limit, 2);
  payload["quantity"] = quantity;
  payload["stopPrice"] = utils::float_::to_currency(prices.open_stop);

  return payload;
}

#endif
