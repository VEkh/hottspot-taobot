#ifndef ALPACA__TAO_BOT_runtime
#define ALPACA__TAO_BOT_runtime

#include "tao_bot.h" // Alpaca::TaoBot

int Alpaca::TaoBot::runtime() {
  if (!this->quotes.size()) {
    return 0;
  }

  return this->quotes.back().timestamp - this->quotes.front().timestamp;
}

#endif
