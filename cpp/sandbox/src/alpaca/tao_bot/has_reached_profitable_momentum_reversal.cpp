#ifndef ALPACA__TAO_BOT_has_reached_profitable_momentum_reversal
#define ALPACA__TAO_BOT_has_reached_profitable_momentum_reversal

/*
 * Alpaca::TaoBot
 * fmt
 * order_t
 * quote_scoreboard_t
 * quote_t
 */
#include "tao_bot.h"

#include "compute_profit.cpp" // compute_profit
#include "lib/formatted.cpp"  // Formatted
#include <iostream>           // std::cout, std::endl
#include <map>                // std::map
#include <stdio.h>            // printf
#include <string>             // std::string

bool Alpaca::TaoBot::has_reached_profitable_momentum_reversal() {
  if (!this->api_client.is_beta()) {
    return false;
  }

  if (this->quotes.empty()) {
    return false;
  }

  if (this->momentum_reversals["resistance"].empty() &&
      this->momentum_reversals["support"].empty()) {
    return false;
  }

  const quote_t current_quote = this->quotes.back();
  std::map<std::string, quote_t>::reverse_iterator it;

  it = this->momentum_reversals["resistance"].rbegin();

  if (current_quote.price > it->second.price) {
    return false;
  }

  it = this->momentum_reversals["support"].rbegin();

  if (current_quote.price < it->second.price) {
    return false;
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
          self->compute_profit(self->open_order_ptr, &quote);
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

  if (scoreboard.score <= 0) {
    return false;
  }

  const double min_profit =
      0.9 * compute_profit(this->open_order_ptr, &scoreboard.quote);

  if (this->open_order_ptr->max_profit >= min_profit &&
      this->open_order_ptr->profit < this->open_order_ptr->max_profit) {
    const Formatted::Stream type_color =
        scoreboard.type == "resistance" ? fmt.green : fmt.red;

    std::cout << fmt.bold << fmt.yellow;
    printf("With a score of %.4f, the", scoreboard.score);
    std::cout << type_color;
    printf(" %s ", scoreboard.type.c_str());
    std::cout << fmt.yellow;
    printf("price of %.2f @ %s successfully acted as the profit target.\n",
           scoreboard.quote.price,
           ::utils::time_::date_string(scoreboard.quote.timestamp / 1000, "%R",
                                       "America/Chicago")
               .c_str());
    std::cout << fmt.reset << std::endl;

    return true;
  }

  return false;
};

#endif
