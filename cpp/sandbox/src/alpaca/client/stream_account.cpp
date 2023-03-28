#ifndef ALPACA__CLIENT_stream_account
#define ALPACA__CLIENT_stream_account

#include "client.h"           // Alpaca::Client, fmt
#include "deps.cpp"           // json, nlohmann
#include "fetch_account.cpp"  // fetch_account
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/io.cpp"   // ::utils::io
#include "lib/utils/json.cpp" // ::utils::json
#include <algorithm>          // std::max
#include <ctime>              // std::time
#include <iostream>           // std::cout, std::endl
#include <math.h>             // abs
#include <string>             // std::stod, std::string
#include <unistd.h>           // usleep

void Alpaca::Client::stream_account() {
  double max_balance = 0.00;
  double original_balance = 0.00;
  double original_margin_buying_power = 0.00;

  while (true) {
    json account_json;

    try {
      account_json = ::utils::json::parse_with_catch(
          fetch_account(), "ALPACA__CLIENT_stream_account");

    } catch (...) {
      usleep(1e6);

      continue;
    }

    try {
      const std::string balance_string = account_json["equity"];
      const double balance = std::stod(balance_string);

      if (!max_balance ||
          max_balance && (abs(max_balance - balance) / max_balance) < 0.1) {
        max_balance = std::max(balance, max_balance);
      }

      if (!original_balance) {
        original_balance = balance;
      }

      if (!original_margin_buying_power) {
        const std::string margin_buying_power = account_json["buying_power"];

        original_margin_buying_power = std::stod(margin_buying_power);
      }

      account_json["max_balance"] = max_balance;
      account_json["original_balance"] = original_balance;
      account_json["original_margin_buying_power"] =
          original_margin_buying_power;
      account_json["timestamp"] = (long int)std::time(nullptr);

      std::cout << fmt.bold << fmt.cyan << account_json.dump(2) << fmt.reset
                << std::endl
                << std::endl;

      const std::string filepath = std::string(DATA_DIR) + "/alpaca/" +
                                   this->config.api_key + "/account.json";

      ::utils::io::write_to_file(account_json.dump(2), filepath.c_str());

      usleep(1e6);
    } catch (nlohmann::detail::type_error &) {
      std::string error_message = Formatted::error_message(
          std::string("[ALPACA__CLIENT_stream_account]: "
                      "nlohmann::detail::type_error when parsing account "
                      "balance. Trying again."));

      std::cout << error_message << fmt.reset << std::endl;

      usleep(1e6);

      continue;
    }
  }
}

#endif
