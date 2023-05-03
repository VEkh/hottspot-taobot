#ifndef OANDA__TAO_BOT_fetch_and_persist_margin_rates
#define OANDA__TAO_BOT_fetch_and_persist_margin_rates

#include "deps.cpp"           // json, nlohmann
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/json.cpp" // ::utils::json
#include "tao_bot.h"          // Oanda::TaoBot
#include <list>               // std::list
#include <string>             // std::string
#include <vector>             // std::vector

void Oanda::TaoBot::fetch_and_persist_margin_rates(
    const std::list<std::string> symbols) {

  try {
    const std::vector<std::string> symbols_vec(symbols.begin(), symbols.end());

    json instruments_json = ::utils::json::parse_with_catch(
        this->api_client.fetch_instruments(symbols_vec),
        "OANDA__TAO_BOT_fetch_and_persist_margin_rates");

    for (json::iterator it = instruments_json.begin();
         it != instruments_json.end(); it++) {
      const std::string margin_rate_string = it.value()["marginRate"];
      const double multiplier = 1.0 / std::stod(margin_rate_string);

      this->db_margin_rate.insert({
          .multiplier = multiplier,
          .symbol = it.key(),
      });
    }
  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(
        std::string("[OANDA__TAO_BOT_fetch_and_persist_margin_rates]: "
                    "nlohmann::detail::type_error when fetching instruments. "
                    "Trying again."));

    std::cout << error_message << std::endl;

    usleep(5e5);

    return fetch_and_persist_margin_rates(symbols);
  }
}

#endif
