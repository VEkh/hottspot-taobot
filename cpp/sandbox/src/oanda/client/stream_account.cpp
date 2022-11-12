#ifndef OANDA__CLIENT_stream_account
#define OANDA__CLIENT_stream_account

#include "client.h"              // Oanda::Client, fmt
#include "deps.cpp"              // json, nlohmann
#include "fetch_account.cpp"     // fetch_account
#include "fetch_instruments.cpp" // fetch_instruments
#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/io.cpp"      // ::utils::io
#include "lib/utils/json.cpp"    // ::utils::json
#include "map_margin_rates.cpp"  // map_margin_rates
#include <algorithm>             // std::max
#include <ctime>                 // std::time
#include <iostream>              // std::cout, std::endl
#include <string>                // std::stod, std::string
#include <unistd.h>              // usleep

void Oanda::Client::stream_account() {
  double max_balance = 0.00;
  double original_balance = 0.00;
  json instruments_json;

  try {

    instruments_json = ::utils::json::parse_with_catch(
        fetch_instruments(::utils::io::tradeable_symbols("oanda")),
        "OANDA__CLIENT_stream_account-fetch_instruments");

  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(
        std::string("[OANDA__CLIENT_stream_account]: "
                    "nlohmann::detail::type_error when fetching instruments. "
                    "Trying again."));

    std::cout << error_message << fmt.reset << std::endl;

    usleep(1e6);
    return stream_account();
  }

  while (true) {
    json account_json;

    try {
      account_json = ::utils::json::parse_with_catch(
          fetch_account(), "OANDA__CLIENT_stream_account");

    } catch (...) {
      usleep(1e6);

      continue;
    }

    try {
      const std::string balance_string = account_json["account"]["balance"];
      const std::string unrealized_pl_string =
          account_json["account"]["unrealizedPL"];

      const double unrealized_pl = std::stod(unrealized_pl_string);
      const double balance = std::stod(balance_string) + unrealized_pl;

      if (!original_balance) {
        original_balance = balance;
      }

      account_json["marginRates"] = map_margin_rates(instruments_json);
      account_json["maxBalance"] = std::max(max_balance, balance);
      account_json["originalBalance"] = original_balance;
      account_json["timestamp"] = (long int)std::time(nullptr);

      std::cout << fmt.bold << fmt.cyan << account_json.dump(2) << fmt.reset
                << std::endl
                << std::endl;

      const std::string filepath =
          std::string(APP_DIR) + "/data/oanda/account.json";

      ::utils::io::write_to_file(account_json.dump(2), filepath.c_str());

      usleep(1e6);
    } catch (nlohmann::detail::type_error &) {
      std::string error_message = Formatted::error_message(std::string(
          "[OANDA__CLIENT_stream_account]: "
          "nlohmann::detail::type_error when parsing account balance. "
          "Trying again."));

      std::cout << error_message << fmt.reset << std::endl;

      usleep(1e6);

      continue;
    }
  }
}

#endif
