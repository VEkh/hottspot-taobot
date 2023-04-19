#ifndef OANDA__TAO_BOT_initialize
#define OANDA__TAO_BOT_initialize

#include "build_performance.cpp"       // build_performance
#include "fetch_and_persist_quote.cpp" // fetch_and_persist_quote
#include "get_account_snapshot.cpp"    // get_account_snapshot
#include "lib/formatted.cpp"           // Formatted::error_message
#include "lib/pg/pg.cpp"               // Pg
#include "lib/utils/boolean.cpp"       // ::utils::boolean
#include "load_price_movement.cpp"     // load_rice_movement
#include "load_quotes.cpp"             // load_quotes
#include "models/quote/quote.cpp"      // DB::Quote
#include "spread_limit.cpp"            // spread_limit
#include "tao_bot.h"                   // Oanda::TaoBot, quantity, symbol
#include <locale.h>                    // setlocale
#include <map>                         // std::map
#include <stdexcept>                   // std::invalid_argument
#include <string>                      // std::map

void Oanda::TaoBot::initialize(const std::string symbol_,
                               std::map<std::string, std::string> &flags_) {
  if (symbol_.empty()) {
    std::string message =
        Formatted::error_message("Must provide a currency pair");

    throw std::invalid_argument(message);
  }

  this->symbol = symbol_;

  if (spread_limit() <= 0) {
    std::string message = Formatted::error_message(
        "Must specify a spread limit for <" + std::string(symbol_) + ">");
    throw std::invalid_argument(message);
  }

  // Support comma separation in print output
  setlocale(LC_NUMERIC, "");

  this->flags = flags_;
  this->pg = Pg(this->flags);
  this->pg.connect();

  this->api_client = Oanda::Client(this->flags);
  this->db_quote = DB::Quote(this->pg);
  this->symbol = symbol_;

  this->account_snapshot = get_account_snapshot();

  load_quotes();
  fetch_and_persist_quote();
  load_price_movement();

  this->init_closed_positions_count = this->closed_positions.size();
  this->performance = build_performance();
}

#endif
