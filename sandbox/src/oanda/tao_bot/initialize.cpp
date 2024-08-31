#ifndef OANDA__TAO_BOT_initialize
#define OANDA__TAO_BOT_initialize

#include "build_performance.cpp"            // build_performance
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "db/candle/candle.cpp"             // DB::Candle
#include "db/margin_rate/margin_rate.cpp"   // DB::MarginRate
#include "db/quote/quote.cpp"               // DB::Quote
#include "initialize_current_trend.cpp"     // initialize_current_trend
#include "lib/forex_availability/forex_availability.cpp" // ForexAvailability
#include "lib/formatted.cpp"           // Formatted::error_message
#include "lib/pg/pg.cpp"               // Pg
#include "lib/utils/boolean.cpp"       // ::utils::boolean
#include "oanda/quote/quote.cpp"       // Oanda::Quote
#include "set_market_open_epoch.cpp"   // set_market_open_epoch
#include "spread_limit.cpp"            // spread_limit
#include "tao_bot.h"                   // Oanda::TaoBot, quantity, symbol
#include "update_account_snapshot.cpp" // update_account_snapshot
#include <locale.h>                    // std::locale
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

  std::locale::global(std::locale("en_US.UTF-8"));

  this->symbol = symbol_;

  if (spread_limit() <= 0) {
    std::string message = Formatted::error_message(
        "Must specify a spread limit for <" + std::string(symbol_) + ">");
    throw std::invalid_argument(message);
  }

  std::locale::global(std::locale("en_US.UTF-8"));

  this->flags = flags_;
  this->pg = Pg(this->flags);
  this->pg.connect();

  this->api_client = Oanda::Client(this->flags);
  this->db_account_stat = DB::AccountStat(this->pg);
  this->db_candle = DB::Candle(this->pg, 1, this->symbol);
  this->db_margin_rate = DB::MarginRate(this->pg);
  this->db_quote = DB::Quote(this->pg);
  this->market_availability = ForexAvailability(this->pg);
  this->quoter = Oanda::Quote(this->pg, this->flags);
  this->symbol = symbol_;

  this->env_symbols = this->api_client.config.env_symbols;

  this->reversals.timeframe_minutes =
      this->api_client.config.reversal_timeframe_minutes;

  set_market_open_epoch();

  initialize_current_trend();
  update_account_snapshot();

  this->performance = build_performance();
}

#endif
