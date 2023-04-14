#ifndef ALPACA__TAO_BOT_target_position_profit
#define ALPACA__TAO_BOT_target_position_profit

// NOTE: Deprecated

#include "dynamic_one_sec_variance.cpp" // dynamic_one_sec_variance
#include "lib/utils/float.cpp"          // ::utils::float_
#include "tao_bot.h"                    // Alpaca::TaoBot

double Alpaca::TaoBot::target_position_profit() {
  const double static_one_sec_variance =
      this->price_movement.three_minute_one_second_variance.average;

  const double min = 0;
  const double max_profit_to_price_movement_ratio =
      this->open_order_ptr->max_profit / static_one_sec_variance;

  const double max = max_profit_to_price_movement_ratio + 25;

  const int duration =
      this->current_epoch - this->open_order_ptr->max_profit_timestamp;

  return ::utils::float_::sigmoid(max, min, duration, -0.005, 2.5 * 60) *
         dynamic_one_sec_variance();
}

#endif
