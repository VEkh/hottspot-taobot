#ifndef ALPACA__TAO_BOT_log_quotes
#define ALPACA__TAO_BOT_log_quotes

#include "hedge_symbol.cpp" // hedge_symbol
#include "log_quote.cpp"    // log_quote
#include "tao_bot.h"        // Alpaca::TaoBot

void Alpaca::TaoBot::log_quotes() {
  log_quote(&this->quotes[this->symbol]);
  log_quote(&this->quotes[hedge_symbol()]);
}

#endif
