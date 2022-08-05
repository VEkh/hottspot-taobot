#ifndef ALPACA__TAO_BOT_get_account_balance
#define ALPACA__TAO_BOT_get_account_balance

#include "deps.cpp"                  // json, nlohmann
#include "fetch_account_balance.cpp" // fetch_account_balance
#include "lib/formatted.cpp"         // Formatted
#include "read_streamed_account.cpp" // read_streamed_account
#include "tao_bot.h"                 // Alpaca::TaoBot
#include <algorithm>                 // std::max, std::min
#include <ctime>                     // std::time
#include <iostream>                  // std::cout, std::endl
#include <math.h>                    // abs
#include <string>                    // std::string, std::to_string

Alpaca::TaoBot::account_balance_t
Alpaca::TaoBot::get_account_balance(const account_balance_t &previous_balance) {
  account_balance_t account_balance_ = get_account_balance();

  const double balance_delta_ratio =
      abs(account_balance_.balance - previous_balance.balance) /
      previous_balance.balance;

  if (balance_delta_ratio > 0.01) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_get_account_balance]: Account balance "
        "spiked by a strange amount: " +
        std::to_string(balance_delta_ratio * 100) + "%. Retrying.");

    std::cout << error_message << fmt.reset << std::endl;

    return get_account_balance(previous_balance);
  }

  account_balance_.max_balance =
      std::max(account_balance_.balance, previous_balance.max_balance);

  account_balance_.min_balance =
      std::min(account_balance_.balance, previous_balance.min_balance);

  return account_balance_;
}

Alpaca::TaoBot::account_balance_t Alpaca::TaoBot::get_account_balance() {
  json account_json;

  try {
    account_json = read_streamed_account();
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_get_account_balance]: "
        "nlohmann::detail::parse_error when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    account_json = fetch_account_balance();
  } catch (std::domain_error &e) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_get_account_balance]: std::domain_error "
        "when streaming: ");
    std::cout << error_message << e.what() << fmt.reset << std::endl;

    account_json = fetch_account_balance();
  } catch (std::invalid_argument &) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_get_account_balance]: std::invalid_argument "
        "when streaming");
    std::cout << error_message << fmt.reset << std::endl;

    account_json = fetch_account_balance();
  }

  try {
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
    return get_account_balance();
  }
}

#endif
