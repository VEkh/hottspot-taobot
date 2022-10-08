#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "current_price.cpp"     // current_price
#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/boolean.cpp" // ::utils::boolean
#include "tao_bot.h" // Alpaca::TaoBot, fmt, quote_scoreboard_t, quote_t
#include <iostream>  // std::cout, std::endl
#include <map>       // std::map
#include <math.h>    // abs
#include <stdio.h>   // printf
#include <string>    // std::string

bool Alpaca::TaoBot::is_next_position_long() {
  if (this->quotes.empty()) {
    return ::utils::boolean::flip_coin();
  }

  if (this->momentum_reversals["resistance"].empty() &&
      this->momentum_reversals["support"].empty()) {
    return ::utils::boolean::flip_coin();
  }

  quote_scoreboard_t scoreboard;

  void (*traverse_momentum_reversals)(Alpaca::TaoBot *, quote_scoreboard_t &,
                                      const char *) =
      [](Alpaca::TaoBot *self, quote_scoreboard_t &scoreboard,
         const char *type) -> void {
    const quote_t current_quote = self->quotes.back();

    std::map<std::string, quote_t> reversals = self->momentum_reversals[type];
    std::map<std::string, quote_t>::iterator it;

    for (it = reversals.begin(); it != reversals.end(); it++) {
      const quote_t quote = it->second;
      const double price_score =
          std::min(100.0, 1 / abs(current_quote.price - quote.price));
      const double time_score =
          1000.0 / (current_quote.timestamp - quote.timestamp);

      const double score = price_score * time_score;

      if (score > scoreboard.score) {
        scoreboard.quote = quote;
        scoreboard.score = score;
        scoreboard.type = type;
      }
    }
  };

  traverse_momentum_reversals(this, scoreboard, "resistance");
  traverse_momentum_reversals(this, scoreboard, "support");

  const Formatted::Stream type_color =
      scoreboard.type == "resistance" ? fmt.green : fmt.red;

  const double current_price_ = current_price();

  std::cout << fmt.bold << fmt.yellow;
  printf("Current Quote: %.2f\n\n", current_price_);
  printf("With a score of %.4f, the", scoreboard.score);
  std::cout << type_color;
  printf(" %s ", scoreboard.type.c_str());
  std::cout << fmt.yellow;
  printf("price of %.2f @ %s is the deciding quote.\n", scoreboard.quote.price,
         ::utils::time_::date_string(scoreboard.quote.timestamp / 1000, "%R",
                                     "America/Chicago")
             .c_str());
  std::cout << fmt.reset << std::endl;

  return current_price_ >= scoreboard.quote.price;
};

#endif
