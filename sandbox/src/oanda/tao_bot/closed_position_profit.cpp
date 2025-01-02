#ifndef OANDA__TAO_BOT_closed_position_profit
#define OANDA__TAO_BOT_closed_position_profit

#include "tao_bot.h" // Oanda::TaoBot, position_t

double Oanda::TaoBot::closed_position_profit(const position_t &position) {
  return position.close_order.profit *
         position.close_order.to_account_currency_ratio *
         position.close_order.quantity;
}

#endif
