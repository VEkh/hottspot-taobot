#ifndef OANDA__TAO_BOT_run
#define OANDA__TAO_BOT_run

#include "log_start_message.cpp" // log_start_message
#include "tao_bot.h"             // Oanda::TaoBot
#include "watch.cpp"             // watch

void Oanda::TaoBot::run() {
  log_start_message();
  // watch();
}

#endif
