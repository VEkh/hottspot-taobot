#ifndef DB__PRICE_ACTION
#define DB__PRICE_ACTION

#include "price_action.h"     // DB::PriceAction, init_args_t
#include "db/quote/quote.cpp" // DB::Quote
#include "db/utils/utils.cpp" // DB::Utils
#include "lib/nyse_availability/nyse_availability.cpp" // NyseAvailability
#include <locale.h>                                    // std::locale
#include <string>                                      // std::stod
#include <time.h>                                      // time

#include "run.cpp"

DB::PriceAction::PriceAction(const init_args_t args) {
  std::locale::global(std::locale("en_US.UTF-8"));

  this->conn = args.conn;
  this->debug = args.debug;
  this->end_at = time(nullptr);
  this->start_at = 0.0;
  this->symbol = args.symbol;
  this->timer_start = time(nullptr);

  this->db_quote = DB::Quote(this->conn);
  this->db_utils = DB::Utils(this->conn);
  this->market_availability = NyseAvailability(this->conn);

  if (!args.end_at.empty()) {
    this->end_at = this->db_utils.timestamp_to_epoch(args.end_at, "UTC");
  }

  if (!args.start_at.empty()) {
    this->start_at = this->db_utils.timestamp_to_epoch(args.start_at, "UTC");
  }

  this->db_utils.set_param({"statement_timeout", "600000"});
}

#endif
