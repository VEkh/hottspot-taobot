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
#include <string>                    // std::stod, std::string, std::to_string
#include <unistd.h>                  // usleep

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

    usleep(5e5);

    return get_account_balance(previous_balance);
  }

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

  account_balance_.overall_max_balance_timestamp =
      account_balance_.balance == account_balance_.overall_max_balance
          ? std::time(nullptr)
          : previous_balance.overall_max_balance_timestamp;

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
  } catch (nlohmann::detail::type_error &) {
    std::string error_message =
        Formatted::error_message("[ALPACA__TAO_BOT_get_account_balance]: "
                                 "nlohmann::detail::type_error when streaming");
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
    const time_t now = std::time(nullptr);

    const double overall_max_balance =
        account_json.contains("max_balance")
            ? (double)account_json["max_balance"]
            : std::max(this->account_balance.overall_max_balance, balance_d);

    const double session_original_balance =
        this->account_balance.session_original_balance
            ? this->account_balance.session_original_balance
            : balance_d;

    double original_balance = this->account_balance.original_balance;

    double original_margin_buying_power =
        this->account_balance.original_margin_buying_power;

    if (!original_balance) {
      original_balance = account_json.contains("original_balance")
                             ? (double)account_json["original_balance"]
                             : balance_d;
    }

    if (!original_margin_buying_power) {
      original_margin_buying_power =
          account_json.contains("original_margin_buying_power")
              ? (double)account_json["original_margin_buying_power"]
              : std::stod(margin_buying_power);
    }

    return {
        .balance = balance_d,
        .margin_buying_power = std::stod(margin_buying_power),
        .margin_multiplier = std::stod(margin_multiplier),
        .max_balance = balance_d,
        .max_balance_timestamp = now,
        .min_balance = balance_d,
        .min_balance_timestamp = now,
        .original_balance = original_balance,
        .original_margin_buying_power = original_margin_buying_power,
        .overall_max_balance = overall_max_balance,
        .overall_max_balance_timestamp = now,
        .session_original_balance = session_original_balance,
        .timestamp = now,
    };
  } catch (nlohmann::detail::parse_error &) {
    return get_account_balance();
  } catch (nlohmann::detail::type_error &) {
    return get_account_balance();
  }
}

#endif
