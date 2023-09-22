#ifndef ALPACA__TAO_BOT_initialize
#define ALPACA__TAO_BOT_initialize

#include "alpaca/client/client.cpp"                 // Alpaca::Client
#include "alpaca/quote/quote.cpp"                   // Alpaca::Quote
#include "backtest/backtest.cpp"                    // Alpaca::TaoBotBacktest
#include "build_performance.cpp"                    // build_performance
#include "db/account_stat/account_stat.cpp"         // DB::AccountStat
#include "db/position/position.cpp"                 // DB::Position
#include "db/utils/utils.cpp"                       // DB::Utils
#include "is_holiday.cpp"                           // is_holiday
#include "lib/formatted.cpp"                        // Formatted::error_message
#include "lib/pg/pg.cpp"                            // Pg
#include "lib/utils/boolean.cpp"                    // ::utils::boolean
#include "lib/utils/io.cpp"                         // ::utils::io
#include "lib/utils/string.cpp"                     // ::utils::string
#include "ml/five_min_predict/five_min_predict.cpp" // ML::FiveMinPredict
#include "tao_bot.h"                                // Alpaca::TaoBot
#include "update_account_snapshot.cpp"              // update_account_snapshot
#include <iostream>                                 // std::cout, std::endl
#include <locale.h>                                 // setlocale
#include <map>                                      // std::map
#include <stdexcept> // std::invalid_argument, std::runtime_error
#include <string>    // std::string
#include <vector>    // std::vector

void Alpaca::TaoBot::initialize(std::string symbol_,
                                std::map<std::string, std::string> &flags_) {
  if (symbol_.empty()) {
    const std::string message =
        Formatted::error_message("Must provide a symbol");

    throw std::invalid_argument(message);
  }

  // Support comma separation in print output
  setlocale(LC_NUMERIC, "");

  this->flags = flags_;
  this->symbol = ::utils::string::upcase(symbol_);

  this->pg = Pg(this->flags);
  this->pg.connect();

  this->backtest = Alpaca::TaoBotBacktest({
      .conn = this->pg,
      .flags = this->flags,
      .symbol = this->symbol,
  });

  if (this->backtest.is_active) {
    this->current_epoch = this->backtest.config.start_epoch;
    this->started_at = this->backtest.config.start_epoch;
  }

  if (is_holiday()) {
    const std::string message = Formatted::error_message(
        "🎉 Today is a holiday! The markets are closed, so go have "
        "fun yabish!! 🥳 ");

    throw std::runtime_error(message);
  }

  this->db_account_stat = DB::AccountStat(this->pg);
  this->db_position = DB::Position(this->pg);
  this->db_utils = DB::Utils(this->pg);
  this->five_min_predict = ML::FiveMinPredict(this->pg, this->symbol);
  this->quoter = Alpaca::Quote(this->pg, this->flags);

  try {
    this->db_utils.set_param({"force_parallel_mode", "on"});
    this->api_client = Alpaca::Client(this->flags);

    std::vector<std::string> tradeable_symbols =
        ::utils::io::tradeable_symbols("alpaca");

    this->tradeable_symbols_count = tradeable_symbols.size();

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
