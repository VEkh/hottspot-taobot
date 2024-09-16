#ifndef OANDA__TAO_BOT_fetch_trade
#define OANDA__TAO_BOT_fetch_trade

#include "deps.cpp"           // json
#include "lib/utils/json.cpp" // ::utils::json
#include "tao_bot.h"          // Oanda::TaoBot, order_t
#include <string>             // std::string

json Oanda::TaoBot::fetch_trade(const order_t *order) {
  const int trade_id = order->trade_id;

  json empty_order;

  if (!trade_id) {
    return empty_order;
  }

  std::string response =
      this->backtest.is_active
          ? this->mock_api_client.fetch_trade(order, this->current_quote)
          : this->api_client.fetch_trade(trade_id);

  return ::utils::json::parse_with_catch(response,
                                         "OANDA__TAO_BOT_fetch_trade");
}

#endif
