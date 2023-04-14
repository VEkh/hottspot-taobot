#ifndef ALPACA__TAO_BOT_write_account_performance
#define ALPACA__TAO_BOT_write_account_performance

#include "deps.cpp"                 // json, nlohmann
#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/io.cpp"         // ::utils::io
#include "lib/utils/time.cpp"       // ::utils::time_
#include "new_positions_opened.cpp" // new_positions_opened
#include "runtime.cpp"              // runtime
#include "tao_bot.h"                // Alpaca::TaoBot
#include <iostream>                 // std::cout, std::endl
#include <stdexcept>                // std::invalid_argument
#include <string>                   // std::string

void Alpaca::TaoBot::write_account_performance() {
  if (!new_positions_opened()) {
    return;
  }

  const std::string filepath = std::string(DATA_DIR) + "/alpaca/sessions/" +
                               this->api_client.config.api_key + ".json";

  json account_performance = {
      {"current_balance", this->account_snapshot.equity},
      {"max_balance", this->account_snapshot.session_max_equity},
      {"max_balance_timestamp",
       this->account_snapshot.session_max_equity_timestamp},
      {"min_balance", this->account_snapshot.min_equity},
      {"min_balance_timestamp", this->account_snapshot.min_equity_timestamp},
      {"original_balance", this->account_snapshot.original_equity},
      {"overall_max_balance", this->account_snapshot.max_equity},
      {"overall_max_balance_timestamp",
       this->account_snapshot.max_equity_timestamp},
      {"runtime", runtime()},
      {"session_original_balance",
       this->account_snapshot.session_original_equity},
  };

  ::utils::io::touch(filepath.c_str(), "{}");
  std::ifstream file;
  json persisted_performances;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> persisted_performances;
    file.close();

    const std::string timestamp_key = ::utils::time_::date_string(
        this->current_epoch, "%FT%R", "America/Chicago");

    persisted_performances[timestamp_key] = account_performance;

    ::utils::io::write_to_file(persisted_performances.dump(2),
                               filepath.c_str());
  } catch (nlohmann::detail::parse_error &) {
    const std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_write_account_performance] Failed to write session "
        "because of `nlohmann::detail::parse_error`");

    std::cout << error_message << std::endl;
  } catch (std::invalid_argument &) {
    const std::string error_message = Formatted::error_message(
        "[ALPACA__TAO_BOT_write_account_performance] Failed to write session "
        "because of `std::invalid_argument`");

    std::cout << error_message << std::endl;
  }
}

#endif
