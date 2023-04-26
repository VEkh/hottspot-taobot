#ifndef ALPACA__TAO_BOT_initialize
#define ALPACA__TAO_BOT_initialize

#include "alpaca/client/client.cpp"             // Alpaca::Client
#include "alpaca/quote/quote.cpp"               // Alpaca::Quote
#include "backtest/backtest.cpp"                // Alpaca::TaoBotBacktest
#include "build_performance.cpp"                // build_performance
#include "is_holiday.cpp"                       // is_holiday
#include "lib/formatted.cpp"                    // Formatted::error_message
#include "lib/pg/pg.cpp"                        // Pg
#include "lib/utils/boolean.cpp"                // ::utils::boolean
#include "lib/utils/string.cpp"                 // ::utils::string
#include "models/account_stat/account_stat.cpp" // DB::AccountStat
#include "models/position/position.cpp"         // DB::Position
#include "tao_bot.h"                            // Alpaca::TaoBot
#include "update_account_snapshot.cpp"          // update_account_snapshot
#include <iostream>                             // std::cout, std::endl
#include <locale.h>                             // setlocale
#include <map>                                  // std::map
#include <stdexcept> // std::invalid_argument, std::runtime_error
#include <string>    // std::string

void Alpaca::TaoBot::initialize(std::string symbol_,
                                std::map<std::string, std::string> &flags_) {
  if (symbol_.empty()) {
    const std::string message =
        Formatted::error_message("Must provide a symbol");

    throw std::invalid_argument(message);
  }

  if (is_holiday()) {
    const std::string message = Formatted::error_message(
        "🎉 Today is a holiday! The markets are closed, so go have "
        "fun yabish!! 🥳 ");

    throw std::runtime_error(message);
  }

  // Support comma separation in print output
  setlocale(LC_NUMERIC, "");

  this->flags = flags_;

  this->pg = Pg(this->flags);
  this->pg.connect();

  this->db_account_stat = DB::AccountStat(this->pg);
  this->db_position = DB::Position(this->pg);
  this->quoter = Alpaca::Quote(this->pg, this->flags);
  this->symbol = ::utils::string::upcase(symbol_);

  try {
    this->api_client = Alpaca::Client(this->flags);
    this->backtest = Alpaca::TaoBotBacktest({
        .conn = this->pg,
        .flags = this->flags,
        .symbol = this->symbol,
    });

    if (this->backtest.is_active) {
      this->current_epoch = this->backtest.config.start_epoch;
      this->started_at = this->backtest.config.start_epoch;
    }

    update_account_snapshot(true);

    this->performance = build_performance();
  } catch (nlohmann::detail::type_error) {
    puts(Formatted::error_message(
             "❌ JSON type error during initialization. Retrying.")
             .c_str());
    return initialize(symbol_, flags_);
  }
}

#endif
