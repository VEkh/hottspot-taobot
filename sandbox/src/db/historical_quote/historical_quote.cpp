#ifndef DB__HISTORICAL_QUOTE
#define DB__HISTORICAL_QUOTE

#include "historical_quote.h"       // DB::HistoricalQuote
#include "alpaca/client/client.cpp" // Alpaca::Client
#include "db/quote/quote.cpp"       // DB::Quote
#include "db/utils/utils.cpp"       // DB::Utils
#include "lib/pg/pg.h"              // Pg
#include <locale.h>                 // std::locale
#include <string>                   // std::stod, std::stoi
#include <time.h>                   // time

#include "download.cpp"

DB::HistoricalQuote::HistoricalQuote(const init_args_t args) {
  std::locale::global(std::locale("en_US.UTF-8"));

  this->conn = args.conn;
  this->db_quote = DB::Quote(this->conn);
  this->db_utils = DB::Utils(this->conn);

  this->api_client = Alpaca::Client(this->conn.flags);
  this->db_utils.set_param({"statement_timeout", "10000"});

  this->batch = std::stoi(args.batch);
  this->debug = args.debug;
  this->symbol = args.symbol;

  if (!args.end_at.empty()) {
    this->end_at = this->db_utils.timestamp_to_epoch(args.end_at, "UTC");
  }

  if (!args.start_at.empty()) {
    this->start_at = this->db_utils.timestamp_to_epoch(args.start_at, "UTC");
  }
}

#endif
