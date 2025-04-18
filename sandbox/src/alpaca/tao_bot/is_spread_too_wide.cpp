#ifndef ALPACA__TAO_BOT_is_spread_too_wide
#define ALPACA__TAO_BOT_is_spread_too_wide

#include "tao_bot.h" // Alpaca::TaoBot, fmt
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf

bool Alpaca::TaoBot::is_spread_too_wide() {
  const double ask = this->current_quote.ask;
  const double bid = this->current_quote.bid;
  const double spread = this->current_quote.spread();
  const double limit = 0.03;

  if (bid == 0) {
    return true;
  }

  const double spread_bid_ratio = spread / bid;

  if (spread_bid_ratio >= limit) {
    std::cout << fmt.bold << fmt.red;
    printf("🛑 Spread is too wide. Can't open.\n   Ask: %'.2f • Bid: %'.2f "
           "• Δ: %.2f (%.2f%%)",
           ask, bid, spread, spread_bid_ratio * 100.0);
    std::cout << fmt.reset << std::endl;

    return true;
  }

  return false;
}

#endif
