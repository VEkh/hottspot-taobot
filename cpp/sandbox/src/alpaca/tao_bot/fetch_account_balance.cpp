#ifndef ALPACA__TAO_BOT_fetch_account_balance
#define ALPACA__TAO_BOT_fetch_account_balance

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "deps.cpp"                 // json, nlohmann
#include "lib/utils/json.cpp"       // ::utils::json
#include "tao_bot.h"                // Alpaca::TaoBot
#include <algorithm>                // std::max, std::min
#include <ctime>                    // std::time
#include <string>                   // std::stod, std::string

json Alpaca::TaoBot::fetch_account_balance(Alpaca::Client &api_client_ref) {
  return ::utils::json::parse_with_catch(
      api_client_ref.fetch_account(), "ALPACA__TAO_BOT_fetch_account_balance");
}

#endif
