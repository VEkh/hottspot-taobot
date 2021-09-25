#ifndef OANDA__TAO_BOT_fetch_account_balance
#define OANDA__TAO_BOT_fetch_account_balance

#include "deps.cpp"  // json
#include "tao_bot.h" // Oanda::TaoBot
#include <string>    // std::stod, std::string

Oanda::TaoBot::account_balance_t Oanda::TaoBot::fetch_account_balance() {
  json account_json = json::parse(this->api_client.fetch_account());

  const std::string balance = account_json["account"]["balance"];
  const std::string margin_buying_power =
      account_json["account"]["marginAvailable"];

  return {
      .balance = std::stod(balance),
      .margin_buying_power = std::stod(margin_buying_power),
  };
}

#endif
