#ifndef ALPACA__TAO_BOT_write_account_performance
#define ALPACA__TAO_BOT_write_account_performance

#include "deps.cpp"                 // json, nlohmann
#include "lib/utils/io.cpp"         // ::utils::io
#include "lib/utils/time.cpp"       // ::utils::time_
#include "new_positions_opened.cpp" // new_positions_opened
#include "runtime.cpp"              // runtime
#include "tao_bot.h"                // Alpaca::TaoBot
#include <ctime>                    // std::time
#include <stdexcept>                // std::invalid_argument
#include <string>                   // std::string

void Alpaca::TaoBot::write_account_performance() {
  if (!new_positions_opened()) {
    return;
  }

  const std::string filepath =
      std::string(APP_DIR) + "/data/alpaca/performance/account.json";

  json account_performance = {
      {"current_balance", this->account_balance.balance},
      {"max_balance", this->account_balance.max_balance},
      {"max_balance_timestamp", this->account_balance.max_balance_timestamp},
      {"min_balance", this->account_balance.min_balance},
      {"min_balance_timestamp", this->account_balance.min_balance_timestamp},
      {"original_balance", this->account_balance.original_balance},
      {"overall_max_balance", this->account_balance.overall_max_balance},
      {"overall_max_balance_timestamp",
       this->account_balance.overall_max_balance_timestamp},
      {"runtime", runtime()},
  };

  std::ifstream file;
  json persisted_performances;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> persisted_performances;
    file.close();
  } catch (nlohmann::detail::parse_error &) {
  } catch (std::invalid_argument &) {
  }

  const long int now = std::time(nullptr);
  const std::string timestamp_key =
      ::utils::time_::date_string(now, "%FT%R", "America/Chicago");

  persisted_performances[timestamp_key] = account_performance;

  ::utils::io::write_to_file(persisted_performances.dump(2), filepath.c_str());
}

#endif
