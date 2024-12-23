#ifndef OANDA__CLIENT_stream_account
#define OANDA__CLIENT_stream_account

#include "client.h"                         // Oanda::Client, fmt
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "db/utils/utils.cpp"               // DB::Utils
#include "deps.cpp"                         // json, nlohmann
#include "fetch_account.cpp"                // fetch_account
#include "lib/formatted.cpp"                // Formatted
#include "lib/pg/pg.cpp"                    // Pg
#include "lib/utils/json.cpp"               // ::utils::json
#include <iostream>                         // std::cout, std::endl
#include <string>                           // std::stod, std::string
#include <time.h>                           // time
#include <unistd.h>                         // usleep

void Oanda::Client::stream_account() {
  Pg pg(this->flags);
  pg.connect();

  DB::AccountStat db_account_stat(pg);
  DB::Utils db_utils(pg);

  db_utils.set_param({"statement_timeout", "1000"});

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
      const std::string equity_string = account_json["account"]["balance"];
      const std::string unrealized_pl_string =
          account_json["account"]["unrealizedPL"];

      const double unrealized_pl = std::stod(unrealized_pl_string);
      const double equity = std::stod(equity_string) + unrealized_pl;

      account_json["timestamp"] = (long int)time(nullptr);

      std::cout << fmt.bold << fmt.cyan;
      std::cout << account_json.dump(2);
      std::cout << fmt.reset << std::endl << std::endl;

      db_account_stat.upsert({
          .api_key_id = this->config.account_id,
          .equity = equity,
          .inserted_at = 0.00,
          .margin_buying_power = 0.00,
          .margin_multiplier = 0.00,
          .debug = true,
      });

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
