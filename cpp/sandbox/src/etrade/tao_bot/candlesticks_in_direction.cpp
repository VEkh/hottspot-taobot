#ifndef ETRADE__TAO_BOT_candlesticks_in_direction
#define ETRADE__TAO_BOT_candlesticks_in_direction

#include "tao_bot.h" // ETrade::TaoBot, candlestick_t, order_action_t
#include <iterator>  // Iter
#include <list>      // std::list

bool ETrade::TaoBot::candlesticks_in_direction(
    const order_action_t order_action, const int sample_size = 3) {
  if (!this->candlesticks.size()) {
    return false;
  }

  std::list<candlestick_t>::reverse_iterator it = this->candlesticks.rbegin();

  int i = sample_size;
  bool out = true;

  if (sample_size == 3) {
    it++;
  }

  while (it != this->candlesticks.rend() && i > 0) {
    const double price_delta = it->close - it->open;

    switch (order_action) {
    case order_action_t::BUY: {
      out = price_delta > 0;

      break;
    }
    case order_action_t::SELL_SHORT: {
      out = price_delta < 0;

      break;
    }
    }

    if (!out) {
      break;
    }

    i--;
    it++;
  }

  return out;
}

#endif
