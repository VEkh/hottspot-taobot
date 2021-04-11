#if !defined ETRADE__STOCK_BOT_shift_transmission_gear
#define ETRADE__STOCK_BOT_shift_transmission_gear

#include "stock_bot.h" // BUY_SELL_RATIO_DOOR_THRESHOLD, ETrade::StockBot, gear_t

void ETrade::StockBot::shift_transmission_gear() {
  if (!this->open_order_ptr) {
    return;
  }

  const double neutral_shift_threshold = 1.0;
  gear_t *transmission_current_gear_ptr = this->transmission.current_gear();

  if (!transmission_current_gear_ptr) {
    return;
  }

  gear_t current_gear = *transmission_current_gear_ptr;

  if (this->is_long_position) {
    if (this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD) {
      current_gear = gear_t::D;
    }

    if (this->long_average_buy_sell_ratio <= neutral_shift_threshold &&
        this->long_average_sell_buy_ratio < BUY_SELL_RATIO_DOOR_THRESHOLD) {
      current_gear = gear_t::N;
    }

    if (this->long_average_sell_buy_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD) {
      current_gear = gear_t::R;
    }
  } else {
    if (this->long_average_sell_buy_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD) {
      current_gear = gear_t::D;
    }

    if (this->long_average_sell_buy_ratio <= neutral_shift_threshold &&
        this->long_average_buy_sell_ratio < BUY_SELL_RATIO_DOOR_THRESHOLD) {
      current_gear = gear_t::N;
    }

    if (this->long_average_buy_sell_ratio >= BUY_SELL_RATIO_DOOR_THRESHOLD) {
      current_gear = gear_t::R;
    }
  }

  if (*transmission_current_gear_ptr != current_gear) {
    this->transmission.shift_gear(current_gear);
  }
}

#endif
