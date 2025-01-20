// TODO: Decide
#ifndef ALPACA__TAO_BOT_stop_profit_type
#define ALPACA__TAO_BOT_stop_profit_type

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h" // Alpaca::TaoBot, reversal_type_t, stop_profit_type_t

Alpaca::TaoBot::stop_profit_type_t
Alpaca::TaoBot::stop_profit_type(const order_t *order) {
  const reversal_type_t reversal_type = order->entry_reversal.type;

  const bool is_reversal_above_threshold =
      day_range_percentile(order->day_candle, order->execution_price) >=
      this->EQUATOR_PERCENTILE;

  if (reversal_type == reversal_type_t::REVERSAL_LOW &&
      is_reversal_above_threshold) {
    return stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE;
  }

  if (reversal_type == reversal_type_t::REVERSAL_HIGH &&
      !is_reversal_above_threshold) {
    return stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE;
  }

  return stop_profit_type_t::STOP_PROFIT_CROSS_RANGE;
}

#endif
