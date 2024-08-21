#ifndef DB__PRICE_ACTION_update_avg
#define DB__PRICE_ACTION_update_avg

#include "price_action.h" // DB::PriceAction

void DB::PriceAction::update_avg() {
  this->days_n++;
  this->price_action_sum += this->day_candle.range_open_percent();

  this->avg_price_action =
      this->days_n ? this->price_action_sum / this->days_n : 0.0;
}

#endif
