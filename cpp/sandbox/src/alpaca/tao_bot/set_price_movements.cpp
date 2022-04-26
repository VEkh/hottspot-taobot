#ifndef ALPACA__TAO_BOT_set_price_movements
#define ALPACA__TAO_BOT_set_price_movements

#include "hedge_symbol.cpp"              // hedge_symbol
#include "price_movement_pair_ratio.cpp" // price_movement_pair_ratio
#include "set_price_movement.cpp"        // set_price_movement
#include "tao_bot.h"                     // Alpaca::TaoBot
#include "write_price_movement.cpp"      // write_price_movement
#include <string>                        // std::string

void Alpaca::TaoBot::set_price_movements() {
  const std::string hedge_symbol_ = hedge_symbol();

  set_price_movement(this->symbol);
  set_price_movement(hedge_symbol_);

  this->price_movements[this->symbol].ratio_to_pair = price_movement_pair_ratio(
      this->quotes[this->symbol], this->quotes[hedge_symbol_],
      this->price_movements[this->symbol].ratio_to_pair);

  write_price_movement(this->symbol, this->price_movements[this->symbol]);
  write_price_movement(hedge_symbol_, this->price_movements[hedge_symbol_]);
}

#endif
