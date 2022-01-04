#ifndef ALPACA__TAO_BOT_fetch_account_balance
#define ALPACA__TAO_BOT_fetch_account_balance

#include "deps.cpp"           // json
#include "lib/utils/json.cpp" // ::utils::json
#include "tao_bot.h"          // Alpaca::TaoBot
#include <string>             // std::stod, std::string

Alpaca::TaoBot::account_balance_t Alpaca::TaoBot::fetch_account_balance() {
  json account_json =
      ::utils::json::parse_with_catch(this->api_client.fetch_account(),
                                      "ALPACA__TAO_BOT_fetch_account_balance");

  const std::string balance = account_json["cash"];
  const std::string margin_buying_power = account_json["buying_power"];

  return {
      .balance = std::stod(balance),
      .margin_buying_power = std::stod(margin_buying_power),
  };
}

#endif
