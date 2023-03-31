#ifndef ALPACA__TAO_BOT_get_account_balance
#define ALPACA__TAO_BOT_get_account_balance

// NOTE: Deprecated

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

Alpaca::TaoBot::account_snapshot_t Alpaca::TaoBot::get_account_balance(
    const account_snapshot_t &previous_balance) {
  account_snapshot_t account_snapshot_ = get_account_balance();

  const double equity_delta_ratio =
      abs(account_snapshot_.equity - previous_balance.equity) /
      previous_balance.equity;

  if (equity_delta_ratio > 0.1) {
    std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_get_account_balance]: Account balance "
        "spiked by a strange amount: " +
        std::to_string(equity_delta_ratio * 100) + "%. Retrying.");

    std::cout << error_message << fmt.reset << std::endl;

    usleep(5e5);

    return get_account_balance(previous_balance);
  }

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

Alpaca::TaoBot::account_snapshot_t Alpaca::TaoBot::get_account_balance() {
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
    const std::string equity = account_json["equity"];
    const std::string margin_buying_power = account_json["buying_power"];
    const std::string margin_multiplier = account_json["multiplier"];

    const double equity_d = std::stod(equity);
    const double now = std::time(nullptr);

    const double max_equity =
        account_json.contains("max_balance")
            ? (double)account_json["max_balance"]
            : std::max(this->account_snapshot.max_equity, equity_d);

    const double session_original_equity =
        this->account_snapshot.session_original_equity
            ? this->account_snapshot.session_original_equity
            : equity_d;

    double original_equity = this->account_snapshot.original_equity;

    double original_margin_buying_power =
        this->account_snapshot.original_margin_buying_power;

    if (!original_equity) {
      original_equity = account_json.contains("original_balance")
                            ? (double)account_json["original_balance"]
                            : equity_d;
    }

    if (!original_margin_buying_power) {
      original_margin_buying_power =
          account_json.contains("original_margin_buying_power")
              ? (double)account_json["original_margin_buying_power"]
              : std::stod(margin_buying_power);
    }

    return {
        .equity = equity_d,
        .margin_buying_power = std::stod(margin_buying_power),
        .margin_multiplier = std::stod(margin_multiplier),
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
  } catch (nlohmann::detail::parse_error &) {
    return get_account_balance();
  } catch (nlohmann::detail::type_error &) {
    return get_account_balance();
  }
}

#endif
