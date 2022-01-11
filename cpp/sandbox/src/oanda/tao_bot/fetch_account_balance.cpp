#ifndef OANDA__TAO_BOT_fetch_account_balance
#define OANDA__TAO_BOT_fetch_account_balance

#include "deps.cpp"           // json
#include "lib/utils/json.cpp" // ::utils::json
#include "tao_bot.h"          // Oanda::TaoBot
#include <math.h>             // floor
#include <string>             // std::stod, std::string

Oanda::TaoBot::account_balance_t Oanda::TaoBot::fetch_account_balance() {
  json account_json = ::utils::json::parse_with_catch(
      this->api_client.fetch_account(),
      "OANDA__TAO_BOT_fetch_account_balance-fetch_account");

  json instrument_json = ::utils::json::parse_with_catch(
      this->api_client.fetch_instrument(this->symbol),
      "OANDA__TAO_BOT_fetch_account_balance-fetch_instrument");

  const std::string balance = account_json["account"]["balance"];
  const std::string margin_rate_string = instrument_json["marginRate"];
  const std::string margin_buying_power_string =
      account_json["account"]["marginAvailable"];

  const double margin_rate = std::stod(margin_rate_string);

  const double margin_buying_power =
      floor(std::stod(margin_buying_power_string)) / margin_rate;

  return {
      .balance = std::stod(balance),
      .margin_buying_power = margin_buying_power,
      .margin_multiplier = (int)(1 / margin_rate),
  };
}

#endif
