#ifndef OANDA__TAO_BOT_fetch_trade
#define OANDA__TAO_BOT_fetch_trade

#include "deps.cpp"           // json
#include "lib/utils/json.cpp" // ::utils::json
#include "tao_bot.h"          // Oanda::TaoBot
#include <string>             // std::string

json Oanda::TaoBot::fetch_trade(const int trade_id) {
  json empty_order;

  if (!trade_id) {
    return empty_order;
  }

  std::string response = this->api_client.fetch_trade(trade_id);

  return ::utils::json::parse_with_catch(response,
                                         "OANDA__TAO_BOT_fetch_trade");
}

#endif
