#ifndef ALPACA__TAO_BOT_initialize
#define ALPACA__TAO_BOT_initialize

#include "alpaca/client/client.cpp"         // Alpaca::Client
#include "alpaca/quote/quote.cpp"           // Alpaca::Quote
#include "alpaca/utils.cpp"                 // Alpaca::Utils
#include "backtest/backtest.cpp"            // Alpaca::TaoBotBacktest
#include "build_performance.cpp"            // build_performance
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "db/candle/candle.cpp"             // DB::Candle
#include "db/position/position.cpp"         // DB::Position
#include "db/utils/utils.cpp"               // DB::Utils
#include "initialize_current_trend.cpp"     // initialize_current_trend
#include "lib/formatted.cpp"                // Formatted::error_message
#include "lib/pg/pg.cpp"                    // Pg
#include "lib/utils/boolean.cpp"            // ::utils::boolean
#include "lib/utils/string.cpp"             // ::utils::string
#include "read_closed_positions.cpp"        // read_closed_positions
#include "set_market_close_epoch.cpp"       // set_market_close_epoch
#include "set_market_open_epoch.cpp"        // set_market_open_epoch
#include "tao_bot.h"                        // Alpaca::TaoBot
#include "update_account_snapshot.cpp"      // update_account_snapshot
#include <iostream>                         // std::cout, std::endl
#include <list>                             // std::list
#include <locale.h>                         // setlocale
#include <map>                              // std::map
#include <stdexcept> // std::invalid_argument, std::runtime_error
#include <string>    // std::string

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

  this->db_account_stat = DB::AccountStat(this->pg);
  this->db_candle = DB::Candle(this->pg, 1, this->symbol);
  this->db_position = DB::Position(this->pg);
  this->db_utils = DB::Utils(this->pg);
  this->quoter = Alpaca::Quote(this->pg, this->flags);

  try {
    this->db_utils.set_param({"force_parallel_mode", "on"});
    this->api_client = Alpaca::Client(this->flags);

    this->env_symbols = this->api_client.config.env_symbols;

    this->backtest = Alpaca::TaoBotBacktest({
        .conn = this->pg,
        .env_symbols = this->env_symbols,
        .flags = this->flags,
        .symbol = this->symbol,
    });

    if (this->backtest.is_active) {
      this->current_epoch = this->backtest.config.start_epoch +
                            this->api_client.config.late_start_seconds;

      this->started_at = this->backtest.config.start_epoch;
    }

    if (this->market_availability.is_holiday(this->current_epoch)) {
      const std::string message = Formatted::error_message(
          "🎉 Today is a holiday! The markets are closed, so go have "
          "fun yabish!! 🥳 ");

      throw std::runtime_error(message);
    }

    this->reversals.timeframe_minutes =
        this->api_client.config.reversal_timeframe_minutes;

    set_market_close_epoch();
    set_market_open_epoch();
    update_account_snapshot(true);
    read_closed_positions();

    this->performance = build_performance();

    initialize_current_trend();
  } catch (nlohmann::detail::type_error) {
    puts(Formatted::error_message(
             "❌ JSON type error during initialization. Retrying.")
             .c_str());
    return initialize(symbol_, flags_);
  }
}

#endif
