#ifndef OANDA__TAO_BOT_convert_price
#define OANDA__TAO_BOT_convert_price

#include "tao_bot.h" // Oanda::TaoBot
#include <string>    // std::string

double Oanda::TaoBot::convert_price(const double price, const std::string from,
                                    const std::string to) {
  const std::string exchange_rate_symbol = from + std::string("_") + to;

  if (from == to) {
    return price;
  }

  const std::string quote_string =
      this->api_client.fetch_quote(exchange_rate_symbol);

  const quote_t exchange_rate_quote =
      this->api_client.parse_quote(quote_string);

  std::cout << fmt.bold << fmt.cyan;
  printf("From: %s @ %.5f • To: %s @ %.5f • Exchange Rate Symbol: %s\n",
         from.c_str(), price, to.c_str(), exchange_rate_quote.price,
         exchange_rate_symbol.c_str());
  std::cout << fmt.reset << std::endl;

  return exchange_rate_quote.price * price;
}

#endif
