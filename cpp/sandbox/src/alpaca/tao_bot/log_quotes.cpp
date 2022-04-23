#ifndef ALPACA__TAO_BOT_log_quotes
#define ALPACA__TAO_BOT_log_quotes

#include "log_quote.cpp" // log_quote
#include "tao_bot.h"     // Alpaca::TaoBot

void Alpaca::TaoBot::log_quotes() {
  log_quote(&this->quotes);
  log_quote(&this->hedge_quotes);
}

#endif
