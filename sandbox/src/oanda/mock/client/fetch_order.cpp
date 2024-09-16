#ifndef OANDA__MOCK__CLIENT_fetch_order
#define OANDA__MOCK__CLIENT_fetch_order

#include "client.h" // Oanda::Mock::Client
#include <stdio.h>  // snprintf
#include <string.h> // strlen
#include <string>   // std::string, std::to_string

std::string Oanda::Mock::Client::fetch_order(const long int epoch) {
  const char *response_format = R"(
    {
      "tradeOpenedID": "%li",
      "state": "FILLED"
    }
  )";

  const size_t response_l =
      strlen(response_format) + std::to_string(epoch).size();

  char response[response_l];

  snprintf(response, response_l, response_format, epoch);

  return response;
}

#endif
