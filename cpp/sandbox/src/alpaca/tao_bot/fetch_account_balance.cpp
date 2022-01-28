#ifndef ALPACA__TAO_BOT_fetch_account_balance
#define ALPACA__TAO_BOT_fetch_account_balance

#include "deps.cpp"           // json, nlohmann
#include "lib/utils/json.cpp" // ::utils::json
#include "tao_bot.h"          // Alpaca::TaoBot
#include <string>             // std::stod, std::string

Alpaca::TaoBot::account_balance_t Alpaca::TaoBot::fetch_account_balance() {
  try {
    json account_json = ::utils::json::parse_with_catch(
        this->api_client.fetch_account(),
        "ALPACA__TAO_BOT_fetch_account_balance");

    const std::string balance = account_json["equity"];
    const std::string margin_buying_power = account_json["buying_power"];
    const std::string margin_multiplier = account_json["multiplier"];

    return {
        .balance = std::stod(balance),
        .margin_buying_power = std::stod(margin_buying_power),
        .margin_multiplier = std::stod(margin_multiplier),
    };
  } catch (nlohmann::detail::type_error &) {
    return fetch_account_balance();
  }
}

#endif
