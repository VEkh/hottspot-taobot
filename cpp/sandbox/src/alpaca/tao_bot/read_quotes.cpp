#ifndef ALPACA__TAO_BOT_read_quotes
#define ALPACA__TAO_BOT_read_quotes

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::read_quotes() {
  this->quotes = this->quoter.read_collection(this->symbol, 2);
}

#endif
