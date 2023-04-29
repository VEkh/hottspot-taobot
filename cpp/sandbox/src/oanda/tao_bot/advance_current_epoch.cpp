#ifndef OANDA__TAO_BOT_advance_current_epoch
#define OANDA__TAO_BOT_advance_current_epoch

#include "tao_bot.h" // Oanda::TaoBot
#include <time.h>    // time
#include <unistd.h>  // usleep

void Oanda::TaoBot::advance_current_epoch() {
  usleep(5e5);

  advance_current_epoch(time(nullptr));
}

void Oanda::TaoBot::advance_current_epoch(const double epoch) {
  this->current_epoch = epoch;
}

#endif
