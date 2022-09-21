#ifndef OANDA__TAO_BOT_get_account_balance
#define OANDA__TAO_BOT_get_account_balance

#include "deps.cpp"                  // json, nlohmann
#include "fetch_account_balance.cpp" // fetch_account_balance
#include "lib/formatted.cpp"         // Formatted
#include "read_streamed_account.cpp" // read_streamed_account
#include "tao_bot.h"                 // Oanda::TaoBot
#include <algorithm>                 // std::max, std::min
#include <ctime>                     // std::time
#include <iostream>                  // std::cout, std::endl
#include <string>                    // std::stod, std::string, std::to_string

Oanda::TaoBot::account_balance_t
Oanda::TaoBot::get_account_balance(const account_balance_t &previous_balance) {
  account_balance_t account_balance_ = get_account_balance();

  account_balance_.max_balance =
      std::max(account_balance_.balance, previous_balance.max_balance);

  account_balance_.max_balance_timestamp =
      account_balance_.balance == account_balance_.max_balance
          ? std::time(nullptr)
          : previous_balance.max_balance_timestamp;

  account_balance_.min_balance =
      std::min(account_balance_.balance, previous_balance.min_balance);

  account_balance_.min_balance_timestamp =
      account_balance_.balance == account_balance_.min_balance
          ? std::time(nullptr)
          : previous_balance.min_balance_timestamp;

  return account_balance_;
}

Oanda::TaoBot::account_balance_t Oanda::TaoBot::get_account_balance() {
  json account_json;

  try {
    account_json = read_streamed_account();
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string("[OANDA__TAO_BOT_get_account_balance]: "
                    "nlohmann::detail::parse_error when streaming"));
    std::cout << error_message << fmt.reset << std::endl;

    account_json = fetch_account_balance();
  } catch (std::domain_error &e) {
    std::string error_message = Formatted::error_message(
        std::string("[OANDA__TAO_BOT_get_account_balance]: std::domain_error "
                    "when streaming: "));
    std::cout << error_message << e.what() << fmt.reset << std::endl;

    account_json = fetch_account_balance();
  } catch (std::invalid_argument &) {
    std::string error_message = Formatted::error_message(std::string(
        "[OANDA__TAO_BOT_get_account_balance]: std::invalid_argument "
        "when streaming"));
    std::cout << error_message << fmt.reset << std::endl;

    account_json = fetch_account_balance();
  }

  try {
    const std::string balance = account_json["account"]["balance"];
    const std::string margin_rate_string =
        account_json["marginRates"][this->symbol];
    const std::string margin_buying_power_string =
        account_json["account"]["marginAvailable"];

    const double margin_rate = std::stod(margin_rate_string);

    const double margin_buying_power =
        floor(std::stod(margin_buying_power_string)) / margin_rate;

    double original_balance = this->account_balance.original_balance;

    const double balance_d = std::stod(balance);
    const time_t now = std::time(nullptr);

    if (!original_balance) {
      original_balance = account_json.contains("originalBalance")
                             ? (double)account_json["originalBalance"]
                             : std::stod(balance);
    }

    const double original_margin_buying_power =
        this->account_balance.original_margin_buying_power
            ? this->account_balance.original_margin_buying_power
            : margin_buying_power;

    return {
        .balance = balance_d,
        .margin_buying_power = margin_buying_power,
        .margin_multiplier = 1 / margin_rate,
        .max_balance = balance_d,
        .max_balance_timestamp = now,
        .min_balance = balance_d,
        .min_balance_timestamp = now,
        .original_balance = original_balance,
        .original_margin_buying_power = original_margin_buying_power,
        .timestamp = now,
    };
  } catch (nlohmann::detail::type_error &) {
    return get_account_balance();
  }
}

#endif
