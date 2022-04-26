#ifndef ALPACA__TAO_BOT_log_signals
#define ALPACA__TAO_BOT_log_signals

#include "log_signal.cpp" // log_signal
#include "tao_bot.h"      // Alpaca::TaoBot

void Alpaca::TaoBot::log_signals() {
  log_signal(this->open_signal, "Open");
  log_signal(this->stop_loss_signal, "Stop Loss");
}

#endif
