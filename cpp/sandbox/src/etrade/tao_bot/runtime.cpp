#ifndef ETRADE__TAO_BOT_runtime
#define ETRADE__TAO_BOT_runtime

#include "tao_bot.h" // ETrade::TaoBot

int ETrade::TaoBot::runtime() {
  if (!this->quotes.size()) {
    return 0;
  }

  return this->quotes.back().timestamp - this->quotes.front().timestamp;
}

#endif
