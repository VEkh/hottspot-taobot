#ifndef ALPACA__TAO_BOT_run
#define ALPACA__TAO_BOT_run

#include "log_start_message.cpp" // log_start_message
#include "tao_bot.h"             // Alpaca::TaoBot
#include "watch.cpp"             // watch

void Alpaca::TaoBot::run() {
  log_start_message();
  watch();
}

#endif
