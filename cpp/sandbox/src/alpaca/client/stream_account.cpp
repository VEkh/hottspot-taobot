#ifndef ALPACA__CLIENT_stream_account
#define ALPACA__CLIENT_stream_account

#include "client.h"                             // Alpaca::Client, fmt
#include "deps.cpp"                             // json, nlohmann
#include "fetch_account.cpp"                    // fetch_account
#include "lib/formatted.cpp"                    // Formatted
#include "lib/pg/pg.cpp"                        // Pg
#include "lib/utils/io.cpp"                     // ::utils::io
#include "lib/utils/json.cpp"                   // ::utils::json
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include <algorithm>                            // std::max
#include <iostream>                             // std::cout, std::endl
#include <math.h>                               // abs
#include <string>                               // std::stod, std::string
#include <time.h>                               // time
#include <unistd.h>                             // usleep

void Alpaca::Client::stream_account() {

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

      account_json["timestamp"] = (long int)time(nullptr);

      std::cout << fmt.bold << fmt.cyan;
      std::cout << account_json.dump(2);
      std::cout << fmt.reset << std::endl << std::endl;

      db_account_stat.upsert({
          .api_key_id = this->config.api_key_id,
          .equity = equity,
          .inserted_at = 0.00,
          .margin_buying_power = margin_buying_power,
          .margin_multiplier = margin_multiplier,
          .debug = true,
      });

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
