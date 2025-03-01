#ifndef OANDA__MOCK__CLIENT_fetch_trade
#define OANDA__MOCK__CLIENT_fetch_trade

#include "client.h" // Oanda::Mock::Client, order_t, quote_t
#include <stdio.h>  // snprintf
#include <string.h> // strlen
#include <string>   // std::string, std::to_string

std::string Oanda::Mock::Client::fetch_trade(const order_t *order,
                                             const quote_t &quote) {
  const char *response_format = R"(
    {
      "initialUnits": "%li",
      "price": "%f",
      "state": "OPEN"
    }
  )";

  const double filled_price =
      order->action == order_action_t::BUY ? quote.ask : quote.bid;

  const size_t response_l = strlen(response_format) +
                            std::to_string(order->quantity).size() +
                            std::to_string(filled_price).size();

  char response[response_l];

  snprintf(response, response_l, response_format, order->quantity,
           filled_price);

  return response;
}

#endif
