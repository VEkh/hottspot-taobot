#ifndef OANDA__TAO_BOT_candlesticks_in_direction
#define OANDA__TAO_BOT_candlesticks_in_direction

#include "tao_bot.h" // Oanda::TaoBot, candlestick_t, order_action_t
#include <list>      // std::list

bool Oanda::TaoBot::candlesticks_in_direction(
    const order_action_t order_action) {
  if (!this->candlesticks.size()) {
    return false;
  }

  std::list<candlestick_t>::iterator it = this->candlesticks.begin();

  int i = 0;
  const int sample_size = 3;
  bool out = true;

  while (it != this->candlesticks.end() && i < sample_size) {
    const double price_delta = it->close - it->open;

    switch (order_action) {
    case order_action_t::BUY: {
      out = price_delta > 0;

      break;
    }
    case order_action_t::SELL: {
      out = price_delta < 0;

      break;
    }
    }

    if (!out) {
      break;
    }

    i++;
    it++;
  }

  return out;
}

#endif
