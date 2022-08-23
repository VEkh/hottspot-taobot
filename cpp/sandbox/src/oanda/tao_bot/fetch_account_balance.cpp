#ifndef OANDA__TAO_BOT_fetch_account_balance
#define OANDA__TAO_BOT_fetch_account_balance

#include "deps.cpp"           // json, nlohmann
#include "lib/utils/json.cpp" // ::utils::json
#include "tao_bot.h"          // Oanda::TaoBot

json Oanda::TaoBot::fetch_account_balance() {
  try {
    json account_json = ::utils::json::parse_with_catch(
        this->api_client.fetch_account(),
        "OANDA__TAO_BOT_fetch_account_balance-fetch_account");

    json instrument_json = ::utils::json::parse_with_catch(
        this->api_client.fetch_instrument(this->symbol),
        "OANDA__TAO_BOT_fetch_account_balance-fetch_instrument");

    account_json["marginRates"] = {
        {this->symbol, instrument_json["marginRate"]},
    };

    return account_json;
  } catch (nlohmann::detail::type_error &) {
    return fetch_account_balance();
  }
}

#endif
