#ifndef OANDA__TAO_BOT_convert_price
#define OANDA__TAO_BOT_convert_price

#include "get_real_time_quote.cpp" // get_real_time_quote
#include "lib/utils/time.cpp"      // ::utils::time_
#include "tao_bot.h"               // Oanda::TaoBot, fmt, quote_t
#include <iostream>                // std::cout
#include <stdio.h>                 // printf
#include <string>                  // std::string
#include <unistd.h>                // usleep

double Oanda::TaoBot::convert_price(const convert_price_args_t args) {
  const double price = args.price;
  const std::string from = args.from;
  const std::string to = args.to;

  if (from == to) {
    return price;
  }

  const std::string exchange_rate_symbol = from + std::string("_") + to;

  const quote_t exchange_rate_quote = get_real_time_quote(exchange_rate_symbol);

  if (exchange_rate_quote.empty()) {
    if (args.debug) {
      std::cout << fmt.bold << fmt.red;
      printf("[OANDA__TAO_BOT_convert_price]: ❗%s quote isn't available at "
             "%s.\nTrying inverse of %s_%s",
             exchange_rate_symbol.c_str(),
             ::utils::time_::date_string(this->current_epoch, "%F %T",
                                         "America/Chicago")
                 .c_str(),
             to.c_str(), from.c_str());
      std::cout << fmt.reset << std::endl;
    }

    if (!this->backtest.is_active) {
      usleep(5e5);
    }

    return price / convert_price({
                       .debug = args.debug,
                       .from = to,
                       .price = 1.0,
                       .to = from,
                   });
  }

  return exchange_rate_quote.mid() * price;
}

#endif
