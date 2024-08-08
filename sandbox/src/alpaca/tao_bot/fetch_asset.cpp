#ifndef ALPACA__TAO_BOT_fetch_asset
#define ALPACA__TAO_BOT_fetch_asset

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "deps.cpp"                 // json
#include "lib/utils/json.cpp"       // ::utils::json
#include "tao_bot.h"                // Alpaca::TaoBot, fmt
#include <string>                   // std::string

json Alpaca::TaoBot::fetch_asset() {
  const std::string asset_response =
      this->backtest.is_active ? this->backtest.fetch_asset()
                               : this->api_client.fetch_asset(this->symbol);

  return ::utils::json::parse_with_catch(asset_response,
                                         "ALPACA__TAO_BOT_fetch_asset");
}

#endif
