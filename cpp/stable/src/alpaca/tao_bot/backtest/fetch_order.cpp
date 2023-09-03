#ifndef ALPACA__TAO_BOT_BACKTEST_fetch_order
#define ALPACA__TAO_BOT_BACKTEST_fetch_order

/*
 * Alpaca::TaoBotBacktest
 * order_action_t
 * order_t
 * quote_t
 */
#include "backtest.h"

#include <stdio.h>  // snprintf
#include <string.h> // strlen
#include <string>   // std::string

std::string Alpaca::TaoBotBacktest::fetch_order(const order_t *order,
                                                const quote_t &last_quote) {
  const char *response_format = R"(
    {
      "filled_avg_price": "%f",
      "status": "filled"
    }
  )";

  const double filled_price =
      order->action == order_action_t::BUY ? last_quote.ask : last_quote.bid;

  const size_t response_l =
      strlen(response_format) + std::to_string(filled_price).size();

  char response[response_l];

  snprintf(response, response_l, response_format, filled_price);

  return response;
}

#endif
