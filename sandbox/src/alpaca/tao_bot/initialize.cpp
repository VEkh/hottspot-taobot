#ifndef ALPACA__TAO_BOT_initialize
#define ALPACA__TAO_BOT_initialize

#include "alpaca/client/client.cpp"              // Alpaca::Client
#include "alpaca/quote/quote.cpp"                // Alpaca::Quote
#include "alpaca/utils.cpp"                      // Alpaca::Utils
#include "build_performance.cpp"                 // build_performance
#include "db/account_stat/account_stat.cpp"      // DB::AccountStat
#include "db/candle/candle.cpp"                  // DB::Candle
#include "db/position/position.cpp"              // DB::Position
#include "db/utils/utils.cpp"                    // DB::Utils
#include "ensure_is_shortable.cpp"               // ensure_is_shortable
#include "ensure_market_is_open.cpp"             // ensure_market_is_open
#include "ensure_symbol.cpp"                     // ensure_symbol
#include "initialize_current_trend.cpp"          // initialize_current_trend
#include "lib/backtest/backtest.cpp"             // Backtest
#include "lib/formatted.cpp"                     // Formatted::error_message
#include "lib/market_availability/nyse/nyse.cpp" // MarketAvailability::Nyse
#include "lib/pg/pg.cpp"                         // Pg
#include "lib/utils/boolean.cpp"                 // ::utils::boolean
#include "lib/utils/string.cpp"                  // ::utils::string
#include "read_closed_positions.cpp"             // read_closed_positions
#include "tao_bot.h"                             // Alpaca::TaoBot
#include "update_account_snapshot.cpp"           // update_account_snapshot
#include <iostream>                              // std::cout, std::endl
#include <list>                                  // std::list
#include <locale.h>                              // std::locale
#include <map>                                   // std::map
#include <string>                                // std::string

void Alpaca::TaoBot::initialize(std::string symbol_,
                                std::map<std::string, std::string> &flags_) {
  std::locale::global(std::locale("en_US.UTF-8"));

  ensure_symbol(symbol_);

  this->flags = flags_;
  this->symbol = ::utils::string::upcase(symbol_);

  this->pg = Pg(this->flags);
  this->pg.connect();

  this->db_account_stat = DB::AccountStat(this->pg);
  this->db_candle = DB::Candle(this->pg, 1, this->symbol);
  this->db_position = DB::Position(this->pg);
  this->db_utils = DB::Utils(this->pg);
  this->market_availability = MarketAvailability::Nyse(this->pg);
  this->quoter = Alpaca::Quote(this->pg, this->flags);

  this->db_utils.set_param({"force_parallel_mode", "on"});

  try {
    this->api_client = Alpaca::Client(this->flags);

    this->env_symbols = this->api_client.config.env_symbols;

    this->backtest = Backtest({
        .api_client_name = "alpaca",
        .conn = this->pg,
        .env_symbols = this->env_symbols,
        .flags = this->flags,
        .symbol = this->symbol,
    });

    if (this->backtest.is_active) {
      this->current_epoch = this->backtest.config.start_epoch;
      this->started_at = this->backtest.config.start_epoch;
    }

    this->market_availability.set_market_epochs(this->current_epoch);
    this->reversals.timeframe_minutes = this->REVERSAL_TIMEFRAME_MINUTES;

    ensure_market_is_open();
    ensure_is_shortable();
    read_closed_positions();

    initialize_current_trend();
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
