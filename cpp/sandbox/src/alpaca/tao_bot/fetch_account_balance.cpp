#ifndef ALPACA__TAO_BOT_fetch_account_balance
#define ALPACA__TAO_BOT_fetch_account_balance

// NOTE: Deprecated

#include "deps.cpp"           // json, nlohmann
#include "lib/utils/json.cpp" // ::utils::json
#include "tao_bot.h"          // Alpaca::TaoBot

json Alpaca::TaoBot::fetch_account_balance() {
  return ::utils::json::parse_with_catch(
      this->api_client.fetch_account(),
      "ALPACA__TAO_BOT_fetch_account_balance");
}

#endif
