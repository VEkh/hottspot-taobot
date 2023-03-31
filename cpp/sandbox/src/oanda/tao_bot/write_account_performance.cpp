#ifndef OANDA__TAO_BOT_write_account_performance
#define OANDA__TAO_BOT_write_account_performance

#include "deps.cpp"                 // json, nlohmann
#include "lib/utils/io.cpp"         // ::utils::io
#include "lib/utils/time.cpp"       // ::utils::time_
#include "new_positions_opened.cpp" // new_positions_opened
#include "runtime.cpp"              // runtime
#include "tao_bot.h"                // Oanda::TaoBot
#include <ctime>                    // std::time
#include <stdexcept>                // std::invalid_argument
#include <string>                   // std::string

#include "lib/formatted.cpp" // Formatted
#include <stdio.h>           // puts

void Oanda::TaoBot::write_account_performance() {
  if (!new_positions_opened()) {
    return;
  }

  const std::string filepath =
      std::string(DATA_DIR) + "/oanda/performance/account.json";

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

  std::ifstream file;
  json persisted_performances;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> persisted_performances;
    file.close();

    const long int now = std::time(nullptr);
    const std::string timestamp_key =
        ::utils::time_::date_string(now, "%FT%R", "America/Chicago");

    persisted_performances[timestamp_key] = account_performance;

    ::utils::io::write_to_file(persisted_performances.dump(2),
                               filepath.c_str());
  } catch (nlohmann::detail::parse_error &) {
    const std::string error_message = Formatted::error_message(
        "[OANDA__TAO_BOT_write_account_performance] Parse error when trying to "
        "write account session.");

    puts(error_message.c_str());
  } catch (std::invalid_argument &) {
    const std::string error_message =
        Formatted::error_message("[OANDA__TAO_BOT_write_account_performance] "
                                 "Invalid argument error when trying to "
                                 "write account session.");

    puts(error_message.c_str());
  }
}

#endif
