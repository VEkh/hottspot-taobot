#ifndef OANDA__TAO_BOT_initialize
#define OANDA__TAO_BOT_initialize

#include "build_performance.cpp"            // build_performance
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "db/candle/candle.cpp"             // DB::Candle
#include "db/margin_rate/margin_rate.cpp"   // DB::MarginRate
#include "db/position/position.cpp"         // DB::Position
#include "db/quote/quote.cpp"               // DB::Quote
#include "db/utils/utils.cpp"               // DB::Utils
#include "ensure_spread_limit.cpp"          // ensure_spread_limit
#include "ensure_symbol.cpp"                // ensure_symbol
#include "initialize_current_trend.cpp"     // initialize_current_trend
#include "lib/forex_availability/forex_availability.cpp" // ForexAvailability
#include "lib/formatted.cpp"           // Formatted::error_message
#include "lib/pg/pg.cpp"               // Pg
#include "lib/utils/boolean.cpp"       // ::utils::boolean
#include "lib/utils/string.cpp"        // ::utils::string
#include "oanda/quote/quote.cpp"       // Oanda::Quote
#include "read_price_action_stats.cpp" // read_price_action_stats
#include "tao_bot.h"                   // Oanda::TaoBot, quantity, symbol
#include "update_account_snapshot.cpp" // update_account_snapshot
#include <locale.h>                    // std::locale
#include <map>                         // std::map
#include <stdexcept>                   // std::invalid_argument
#include <string>                      // std::map

void Oanda::TaoBot::initialize(const std::string symbol_,
                               std::map<std::string, std::string> &flags_) {
  std::locale::global(std::locale("en_US.UTF-8"));

  ensure_symbol(symbol_);

  this->symbol = ::utils::string::upcase(symbol_);

  ensure_spread_limit();

  this->flags = flags_;

  this->pg = Pg(this->flags);
  this->pg.connect();

  this->db_account_stat = DB::AccountStat(this->pg);
  this->db_candle = DB::Candle(this->pg, 1, this->symbol);
  this->db_margin_rate = DB::MarginRate(this->pg);
  this->db_position = DB::Position(this->pg);
  this->db_quote = DB::Quote(this->pg);
  this->db_utils = DB::Utils(this->pg);
  this->market_availability = ForexAvailability(this->pg);
  this->quoter = Oanda::Quote(this->pg, this->flags);

  this->db_utils.set_param({"force_parallel_mode", "on"});

  this->api_client = Oanda::Client(this->flags);

  this->db_price_action = DB::PriceAction({
      .conn = this->pg,
      .debug = this->api_client.config.debug_sql,
      .symbol = this->symbol,
  });

  this->env_symbols = this->api_client.config.env_symbols;

  this->reversals.timeframe_minutes =
      this->api_client.config.reversal_timeframe_minutes;

  this->market_availability.set_market_close_epoch(this->current_epoch);
  this->market_availability.set_market_open_epoch(this->current_epoch);

  initialize_current_trend();
  read_price_action_stats();
  update_account_snapshot();

  this->performance = build_performance();
}

#endif
