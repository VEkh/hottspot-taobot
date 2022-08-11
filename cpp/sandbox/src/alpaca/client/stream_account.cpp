#ifndef ALPACA__CLIENT_stream_account
#define ALPACA__CLIENT_stream_account

#include "client.h"           // Alpaca::Client, fmt
#include "deps.cpp"           // json, nlohmann
#include "fetch_account.cpp"  // fetch_account
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/io.cpp"   // ::utils::io
#include "lib/utils/json.cpp" // ::utils::json
#include <ctime>              // std::time
#include <iostream>           // std::cout, std::endl
#include <unistd.h>           // usleep

void Alpaca::Client::stream_account() {
  double original_margin_buying_power = 0.00;

  while (true) {
    json account_json;

    try {
      account_json = ::utils::json::parse_with_catch(
          fetch_account(), "ALPACA__CLIENT_stream_account");

    } catch (nlohmann::detail::type_error &) {
      std::string error_message = Formatted::error_message(std::string(
          "[ALPACA__CLIENT_stream_account]: "
          "nlohmann::detail::type_error when fetching quote. Trying again."));

      std::cout << error_message << fmt.reset << std::endl;

      usleep(1e6);

      continue;
    }

    if (!original_margin_buying_power) {
      const std::string margin_buying_power = account_json["buying_power"];

      original_margin_buying_power = std::stod(margin_buying_power);
    }

    account_json["original_margin_buying_power"] = original_margin_buying_power;
    account_json["timestamp"] = (long int)std::time(nullptr);

    std::cout << fmt.bold << fmt.cyan << account_json.dump(2) << fmt.reset
              << std::endl
              << std::endl;

    const std::string filepath =
        std::string(APP_DIR) + "/data/alpaca/account.json";

    ::utils::io::write_to_file(account_json.dump(2), filepath.c_str());

    usleep(1e6);
  }
}

#endif
