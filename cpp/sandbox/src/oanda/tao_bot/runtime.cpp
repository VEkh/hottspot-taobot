#ifndef OANDA__TAO_BOT_runtime
#define OANDA__TAO_BOT_runtime

#include "tao_bot.h" // Oanda::TaoBot

int Oanda::TaoBot::runtime() {
  if (!this->quotes.size()) {
    return 0;
  }

  return this->quotes.back().timestamp - this->quotes.front().timestamp;
}

#endif
