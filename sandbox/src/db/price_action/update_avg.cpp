#ifndef DB__PRICE_ACTION_update_avg
#define DB__PRICE_ACTION_update_avg

#include "price_action.h" // DB::PriceAction, build_state_t

void DB::PriceAction::update_avg(build_state_t &state) {
  state.days_n++;
  state.price_action_sum += state.day_candle.range_open_percent();

  state.avg_price_action =
      state.days_n ? state.price_action_sum / state.days_n : 0.0;
}

#endif
