#ifndef ALPACA__TAO_BOT_price_movement_ratio
#define ALPACA__TAO_BOT_price_movement_ratio

#include "tao_bot.h" // Alpaca::TaoBot
#include <string>    // std::string

double Alpaca::TaoBot::price_movement_ratio(const std::string symbol_) {
  return this->price_movements.short_term_three_minute_one_second_variance
             .average /
         this->price_movements.three_minute_one_second_variance.average;
}

#endif
