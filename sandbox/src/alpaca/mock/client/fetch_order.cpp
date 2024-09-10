#ifndef ALPACA__MOCK__CLIENT_fetch_order
#define ALPACA__MOCK__CLIENT_fetch_order

#include "client.h" // Alpaca::Mock::Client, order_action_t, order_t, quote_t
#include <stdio.h>  // snprintf
#include <string.h> // strlen
#include <string>   // std::string

std::string Alpaca::Mock::Client::fetch_order(const order_t *order,
                                              const quote_t &quote) {
  const char *response_format = R"(
    {
      "filled_avg_price": "%f",
      "status": "filled"
    }
  )";

  const double filled_price =
      order->action == order_action_t::BUY ? quote.ask : quote.bid;

  const size_t response_l =
      strlen(response_format) + std::to_string(filled_price).size();

  char response[response_l];

  snprintf(response, response_l, response_format, filled_price);

  return response;
}

#endif
