#ifndef ALPACA__TAO_BOT_ensure_is_shortable
#define ALPACA__TAO_BOT_ensure_is_shortable

#include "deps.cpp"           // json
#include "fetch_asset.cpp"    // fetch_asset
#include "lib/formatted.cpp"  // Formatted::error_message
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot
#include <stdexcept>          // std::invalid_argument
#include <string>             // std::string

void Alpaca::TaoBot::ensure_is_shortable() {
  json asset_json = fetch_asset();

  const bool is_shortable = asset_json["shortable"];

  if (is_shortable) {
    return;
  }

  const std::string curent_timestamp = ::utils::time_::date_string(
      this->current_epoch, "%F %R CT", "America/Chicago");

  const std::string error_message = Formatted::error_message(
      "❗" + this->symbol + " is not shortable as of " + curent_timestamp);

  throw std::invalid_argument(error_message);
}

#endif
