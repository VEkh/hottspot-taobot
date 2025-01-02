#ifndef OANDA__TAO_BOT_set_to_account_currency_ratio
#define OANDA__TAO_BOT_set_to_account_currency_ratio

#include "convert_price.cpp" // convert_price
#include "tao_bot.h"         // Oanda::TaoBot, order_t

void Oanda::TaoBot::set_to_account_currency_ratio(order_t *order) {
  if (!this->backtest.should_exec_slow_query(this->current_epoch)) {
    return;
  }

  order->to_account_currency_ratio = convert_price({
      .from = order->currency,
      .price = 1.0,
      .to = order->account_currency,
  });
}

#endif
