#ifndef OANDA__TAO_BOT_runtime
#define OANDA__TAO_BOT_runtime

#include "tao_bot.h" // Oanda::TaoBot
#include <ctime>     // std::time

int Oanda::TaoBot::runtime() { return std::time(nullptr) - this->started_at; }

#endif
