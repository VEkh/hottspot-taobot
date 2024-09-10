#ifndef DB__PRICE_ACTION
#define DB__PRICE_ACTION

#include "price_action.h"     // DB::PriceAction, init_args_t
#include "db/quote/quote.cpp" // DB::Quote
#include "db/utils/utils.cpp" // DB::Utils
#include "lib/nyse_availability/nyse_availability.cpp" // NyseAvailability
#include <locale.h>                                    // std::locale

#include "build.cpp"
#include "get_stats.cpp"

DB::PriceAction::PriceAction(const init_args_t args) {
  std::locale::global(std::locale("en_US.UTF-8"));

  this->conn = args.conn;
  this->debug = args.debug;
  this->symbol = args.symbol;

  this->db_quote = DB::Quote(this->conn);
  this->db_utils = DB::Utils(this->conn);
  this->market_availability =
      NyseAvailability(this->conn); // TODO: Extend to forex

  this->db_utils.set_param({"statement_timeout", "6000000"});
}

#endif
