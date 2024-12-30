#ifndef OANDA__TAO_BOT_initialize
#define OANDA__TAO_BOT_initialize

#include "build_performance.cpp"                   // build_performance
#include "db/account_stat/account_stat.cpp"        // DB::AccountStat
#include "db/candle/candle.cpp"                    // DB::Candle
#include "db/margin_rate/margin_rate.cpp"          // DB::MarginRate
#include "db/position/position.cpp"                // DB::Position
#include "db/quote/quote.cpp"                      // DB::Quote
#include "db/utils/utils.cpp"                      // DB::Utils
#include "ensure_market_is_open.cpp"               // ensure_market_is_open
#include "ensure_spread_limit.cpp"                 // ensure_spread_limit
#include "ensure_symbol.cpp"                       // ensure_symbol
#include "lib/backtest/backtest.cpp"               // Backtest
#include "lib/formatted.cpp"                       // Formatted::error_message
#include "lib/market_availability/forex/forex.cpp" // MarketAvailability::Forex
#include "lib/pg/pg.cpp"                           // Pg
#include "lib/utils/boolean.cpp"                   // ::utils::boolean
#include "lib/utils/string.cpp"                    // ::utils::string
#include "oanda/quote/quote.cpp"                   // Oanda::Quote
#include "read_closed_positions.cpp"               // read_closed_positions
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
  this->market_availability = MarketAvailability::Forex(this->pg);
  this->quoter = Oanda::Quote(this->pg, this->flags);

  this->db_utils.set_param({"force_parallel_mode", "on"});

  this->api_client = Oanda::Client(this->flags);

  this->env_symbols = this->api_client.config.env_symbols;

  this->backtest = Backtest({
      .api_client_name = "oanda",
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
  read_closed_positions();

  update_account_snapshot();

  this->performance = build_performance();
}

#endif
