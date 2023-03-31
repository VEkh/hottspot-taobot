#ifndef OANDA__TAO_BOT_get_account_snapshot
#define OANDA__TAO_BOT_get_account_snapshot

#include "deps.cpp"                   // json, nlohmann
#include "fetch_account_snapshot.cpp" // fetch_account_snapshot
#include "lib/formatted.cpp"          // Formatted
#include "read_streamed_account.cpp"  // read_streamed_account
#include "tao_bot.h"                  // Oanda::TaoBot
#include <algorithm>                  // std::max, std::min
#include <ctime>                      // std::time
#include <iostream>                   // std::cout, std::endl
#include <string>                     // std::stod, std::string, std::to_string

Oanda::TaoBot::account_snapshot_t Oanda::TaoBot::get_account_snapshot(
    const account_snapshot_t &previous_balance) {
  account_snapshot_t account_snapshot_ = get_account_snapshot();

  account_snapshot_.session_max_equity =
      std::max(account_snapshot_.equity, previous_balance.session_max_equity);

  account_snapshot_.session_max_equity_timestamp =
      account_snapshot_.equity == account_snapshot_.session_max_equity
          ? std::time(nullptr)
          : previous_balance.session_max_equity_timestamp;

  account_snapshot_.min_equity =
      std::min(account_snapshot_.equity, previous_balance.min_equity);

  account_snapshot_.min_equity_timestamp =
      account_snapshot_.equity == account_snapshot_.min_equity
          ? std::time(nullptr)
          : previous_balance.min_equity_timestamp;

  account_snapshot_.max_equity_timestamp =
      account_snapshot_.equity == account_snapshot_.max_equity
          ? std::time(nullptr)
          : previous_balance.max_equity_timestamp;

  return account_snapshot_;
}

Oanda::TaoBot::account_snapshot_t Oanda::TaoBot::get_account_snapshot() {
  json account_json;

  try {
    account_json = read_streamed_account();
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string("[OANDA__TAO_BOT_get_account_snapshot]: "
                    "nlohmann::detail::parse_error when streaming"));
    std::cout << error_message << fmt.reset << std::endl;

    account_json = fetch_account_snapshot();
  } catch (std::domain_error &e) {
    std::string error_message = Formatted::error_message(
        std::string("[OANDA__TAO_BOT_get_account_snapshot]: std::domain_error "
                    "when streaming: "));
    std::cout << error_message << e.what() << fmt.reset << std::endl;

    account_json = fetch_account_snapshot();
  } catch (std::invalid_argument &) {
    std::string error_message = Formatted::error_message(std::string(
        "[OANDA__TAO_BOT_get_account_snapshot]: std::invalid_argument "
        "when streaming"));
    std::cout << error_message << fmt.reset << std::endl;

    account_json = fetch_account_snapshot();
  }

  try {
    const std::string equity = account_json["account"]["balance"];
    const std::string unrealized_pl_string =
        account_json["account"]["unrealizedPL"];
    const std::string margin_rate_string =
        account_json["marginRates"][this->symbol];
    const std::string margin_buying_power_string =
        account_json["account"]["marginAvailable"];

    const double margin_rate = std::stod(margin_rate_string);

    const double margin_buying_power =
        floor(std::stod(margin_buying_power_string)) / margin_rate;

    double original_equity = this->account_snapshot.original_equity;

    const double equity_d = std::stod(equity) + std::stod(unrealized_pl_string);
    const double now = std::time(nullptr);

    const double session_original_equity =
        this->account_snapshot.session_original_equity
            ? this->account_snapshot.session_original_equity
            : equity_d;

    if (!original_equity) {
      original_equity = account_json.contains("originalBalance")
                            ? (double)account_json["originalBalance"]
                            : equity_d;
    }

    const double max_equity =
        account_json.contains("maxBalance")
            ? (double)account_json["maxBalance"]
            : std::max(this->account_snapshot.max_equity, equity_d);

    const double original_margin_buying_power =
        this->account_snapshot.original_margin_buying_power
            ? this->account_snapshot.original_margin_buying_power
            : margin_buying_power;

    return {
        .equity = equity_d,
        .margin_buying_power = margin_buying_power,
        .margin_multiplier = 1 / margin_rate,
        .max_equity = max_equity,
        .max_equity_timestamp = now,
        .min_equity = equity_d,
        .min_equity_timestamp = now,
        .original_equity = original_equity,
        .original_margin_buying_power = original_margin_buying_power,
        .session_max_equity = equity_d,
        .session_max_equity_timestamp = now,
        .session_original_equity = session_original_equity,
        .timestamp = now,
    };
  } catch (nlohmann::detail::type_error &) {
    return get_account_snapshot();
  }
}

#endif
