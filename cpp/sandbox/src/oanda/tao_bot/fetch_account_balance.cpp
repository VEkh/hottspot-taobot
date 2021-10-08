#ifndef OANDA__TAO_BOT_fetch_account_balance
#define OANDA__TAO_BOT_fetch_account_balance

#include "deps.cpp"  // json
#include "tao_bot.h" // Oanda::TaoBot
#include <string>    // std::stod, std::string

Oanda::TaoBot::account_balance_t Oanda::TaoBot::fetch_account_balance() {
  json account_json = json::parse(this->api_client.fetch_account());

  const std::string balance = account_json["account"]["balance"];
  const std::string margin_rate_string = account_json["account"]["marginRate"];
  const std::string margin_buying_power_string =
      account_json["account"]["marginAvailable"];

  const double margin_rate = std::stod(margin_rate_string);

  const double margin_buying_power =
      std::stod(margin_buying_power_string) / margin_rate;

  return {
      .balance = std::stod(balance),
      .margin_buying_power = margin_buying_power,
  };
}

#endif
