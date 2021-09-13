#ifndef ETRADE__TAO_BOT_run
#define ETRADE__TAO_BOT_run

#include "log_start_message.cpp" // log_start_message
#include "tao_bot.h"           // ETrade::TaoBot
#include "watch.cpp"             // watch

void ETrade::TaoBot::run() {
  log_start_message();
  watch();
}

#endif
