#ifndef OANDA__TAO_BOT_run
#define OANDA__TAO_BOT_run

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::run() {
  printf("Launching TaoBot for the <%s> currency pair\n", this->symbol);
}

#endif
