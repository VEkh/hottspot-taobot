#ifndef OANDA__TAO_BOT_convert_price
#define OANDA__TAO_BOT_convert_price

#include "tao_bot.h" // Oanda::TaoBot, fmt
#include <iostream>  // std::cout
#include <regex>     // std::regex, std::regex_constants, std::regex_search
#include <stdio.h>   // printf
#include <string>    // std::string

double Oanda::TaoBot::convert_price(const double price, const std::string from,
                                    const std::string to) {
  const std::string exchange_rate_symbol = from + std::string("_") + to;

  if (from == to) {
    return price;
  }

  const std::string quote_string =
      this->api_client.fetch_quote(exchange_rate_symbol);

  if (std::regex_search(
          quote_string,
          std::regex("invalid value specified", std::regex_constants::icase))) {

    std::cout << fmt.bold << fmt.red;
    printf("🚩 %s quote isn't available. Trying inverse: %s_%s.\n",
           exchange_rate_symbol.c_str(), to.c_str(), from.c_str());
    std::cout << fmt.reset;

    return 1 / convert_price(price, to, from);
  }

  const quote_t exchange_rate_quote =
      this->api_client.parse_quote(quote_string);

  return exchange_rate_quote.mid() * price;
}

#endif
