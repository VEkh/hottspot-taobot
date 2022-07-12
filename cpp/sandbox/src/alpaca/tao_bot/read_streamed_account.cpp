#ifndef ALPACA__TAO_BOT_read_streamed_account
#define ALPACA__TAO_BOT_read_streamed_account

#include "deps.cpp"           // json, nlohmann
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, quote_t
#include <ctime>              // std::tm, std::mktime
#include <fstream>            // std::ifstream
#include <stdexcept>          // std::domain_error
#include <string>             // std::string

json Alpaca::TaoBot::read_streamed_account() {
  const std::string filepath =
      std::string(APP_DIR) + "/data/alpaca/account.json";

  std::ifstream file;
  json account_json;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> account_json;
    file.close();
  } catch (nlohmann::detail::parse_error &) {
    return read_streamed_account();
  }

  const long int account_epoch = account_json["timestamp"];
  const long int now = std::time(nullptr);

  if ((now - account_epoch) > 30) {
    const std::string error_message =
        Formatted::error_message("Account info stale. Falling back to fetch.");

    throw std::domain_error(error_message);
  }

  return account_json;
}

#endif
