#ifndef ALPACA__TAO_BOT_fetch_account_balance
#define ALPACA__TAO_BOT_fetch_account_balance

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "deps.cpp"                 // json, nlohmann
#include "lib/utils/json.cpp"       // ::utils::json
#include "tao_bot.h"                // Alpaca::TaoBot
#include <algorithm>                // std::max, std::min
#include <ctime>                    // std::time
#include <string>                   // std::stod, std::string

Alpaca::TaoBot::account_balance_t Alpaca::TaoBot::fetch_account_balance(
    Alpaca::Client &api_client_ref, const account_balance_t &previous_balance) {
  account_balance_t account_balance_ = fetch_account_balance(api_client_ref);

  account_balance_.max_balance =
      std::max(account_balance_.balance, previous_balance.max_balance);

  account_balance_.min_balance =
      std::min(account_balance_.balance, previous_balance.min_balance);

  return account_balance_;
}

Alpaca::TaoBot::account_balance_t
Alpaca::TaoBot::fetch_account_balance(Alpaca::Client &api_client_ref) {
  try {
    json account_json = ::utils::json::parse_with_catch(
        api_client_ref.fetch_account(),
        "ALPACA__TAO_BOT_fetch_account_balance");

    const std::string balance = account_json["equity"];
    const std::string margin_buying_power = account_json["buying_power"];
    const std::string margin_multiplier = account_json["multiplier"];

    const double balance_d = std::stod(balance);

    return {
        .balance = balance_d,
        .margin_buying_power = std::stod(margin_buying_power),
        .margin_multiplier = std::stod(margin_multiplier),
        .max_balance = balance_d,
        .min_balance = balance_d,
        .timestamp = std::time(nullptr),
    };
  } catch (nlohmann::detail::type_error &) {
    return fetch_account_balance(api_client_ref);
  }
}

#endif
