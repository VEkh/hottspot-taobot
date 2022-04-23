#ifndef ALPACA__TAO_BOT_log_quote
#define ALPACA__TAO_BOT_log_quote

/*
 * Alpaca::TaoBot
 * fmt
 * quote_t
 */
#include "tao_bot.h"

#include "converted_signaler_price.cpp" // converted_signaler_price
#include "lib/formatted.cpp"            // Formatted
#include "lib/utils/float.cpp"          // utils::float_
#include "lib/utils/integer.cpp"        // utils::integer_
#include <iostream>                     // std::cout, std::endl
#include <stdio.h>                      // printf

void Alpaca::TaoBot::log_quote(const std::string &symbol_) {
  Formatted::Stream log_color = fmt.yellow;

  const std::vector<quote_t> quotes_ = this->quotes[symbol_];
  const int ticks = quotes_.size();

  if (!ticks) {
    return;
  }

  const quote_t *previous_quote =
      ticks > 1 ? &(quotes_.at(ticks - 2)) : nullptr;

  const quote_t current_quote = quotes_.back();

  if (previous_quote) {
    if (current_quote.price > previous_quote->price) {
      log_color = fmt.green;
    } else if (current_quote.price < previous_quote->price) {
      log_color = fmt.red;
    }
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s Quote\n", current_quote.symbol.c_str());

  std::cout << fmt.reset << fmt.bold << log_color;
  printf("Current: %'.2f\n", ::utils::float_::to_currency(current_quote.price));

  if (this->signal.signaler == symbol_) {
    const double signaled_price = current_price(this->signal.signaled);
    const double converted_signaler_price_ = converted_signaler_price();

    const double price_delta_ratio =
        (converted_signaler_price_ - signaled_price) / signaled_price;

    printf("🔁 As Signaled: %'.2f • Δ Ratio %+.2f%%\n",
           ::utils::float_::to_currency(converted_signaler_price_),
           price_delta_ratio * 100.0);
  }

  std::cout << fmt.reset << std::endl;
}

#endif
