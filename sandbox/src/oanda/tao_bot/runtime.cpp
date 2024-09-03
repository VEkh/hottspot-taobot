#ifndef OANDA__TAO_BOT_runtime
#define OANDA__TAO_BOT_runtime

#include "tao_bot.h" // Oanda::TaoBot

int Oanda::TaoBot::runtime() { return this->current_epoch - this->started_at; }

#endif
