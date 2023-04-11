#ifndef ALPACA__CLIENT_stream_account
#define ALPACA__CLIENT_stream_account

#include "client.h"                             // Alpaca::Client, fmt
#include "deps.cpp"                             // json, nlohmann
#include "fetch_account.cpp"                    // fetch_account
#include "lib/formatted.cpp"                    // Formatted
#include "lib/pg/pg.cpp"                        // Pg
#include "lib/utils/io.cpp"                     // ::utils::io
#include "lib/utils/json.cpp"                   // ::utils::json
#include "models/account_stat/account_stat.cpp" // DB::AccountStat
#include <algorithm>                            // std::max
#include <ctime>                                // std::time
#include <iostream>                             // std::cout, std::endl
#include <math.h>                               // abs
#include <string>                               // std::stod, std::string
#include <unistd.h>                             // usleep

void Alpaca::Client::stream_account() {
  double max_equity = 0.00;
  double original_equity = 0.00;
  double original_margin_buying_power = 0.00;

  Pg pg(this->flags);
  pg.connect();

  DB::AccountStat db_account_stat(pg);

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
      const std::string equity_string = account_json["equity"];
      const std::string margin_buying_power_string =
          account_json["buying_power"];

      const std::string margin_multiplier_string = account_json["multiplier"];

      const double equity = std::stod(equity_string);
      const double margin_buying_power = std::stod(margin_buying_power_string);
      const double margin_multiplier = std::stod(margin_multiplier_string);

      if (!max_equity ||
          max_equity && (abs(max_equity - equity) / max_equity) < 0.1) {
        max_equity = std::max(equity, max_equity);
      }

      if (!original_equity) {
        original_equity = equity;
      }

      if (!original_margin_buying_power) {
        original_margin_buying_power = margin_buying_power;
      }

      account_json["max_balance"] = max_equity;
      account_json["original_balance"] = original_equity;
      account_json["original_margin_buying_power"] =
          original_margin_buying_power;
      account_json["timestamp"] = (long int)std::time(nullptr);

      std::cout << fmt.bold << fmt.cyan << account_json.dump(2) << fmt.reset
                << std::endl
                << std::endl;

      const std::string filepath = std::string(DATA_DIR) + "/alpaca/" +
                                   this->config.api_key + "/account.json";

      db_account_stat.upsert({
          .api_key_id = this->config.api_key_id,
          .equity = equity,
          .inserted_at = 0.00,
          .margin_buying_power = margin_buying_power,
          .margin_multiplier = margin_multiplier,
          .debug = true,
      });

      ::utils::io::write_to_file(account_json.dump(2), filepath.c_str());

      usleep(1e6);
    } catch (nlohmann::detail::type_error &) {
      std::string error_message = Formatted::error_message(
          std::string("[ALPACA__CLIENT_stream_account]: "
                      "nlohmann::detail::type_error when parsing account "
                      "stats. Trying again."));

      std::cout << error_message << fmt.reset << std::endl;

      usleep(1e6);

      continue;
    }
  }

  pg.disconnect();
}

#endif
