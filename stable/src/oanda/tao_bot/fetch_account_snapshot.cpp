#ifndef OANDA__TAO_BOT_fetch_account_snapshot
#define OANDA__TAO_BOT_fetch_account_snapshot

#include "deps.cpp"           // json, nlohmann
#include "lib/utils/json.cpp" // ::utils::json
#include "tao_bot.h"          // Oanda::TaoBot

json Oanda::TaoBot::fetch_account_snapshot() {
  try {
    json account_json = ::utils::json::parse_with_catch(
        this->api_client.fetch_account(),
        "OANDA__TAO_BOT_fetch_account_snapshot-fetch_account");

    return account_json;
  } catch (nlohmann::detail::type_error &) {
    return fetch_account_snapshot();
  }
}

#endif
