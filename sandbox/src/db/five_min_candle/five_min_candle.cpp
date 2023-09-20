#ifndef DB__FIVE_MIN_CANDLE
#define DB__FIVE_MIN_CANDLE

#include "build.cpp"
#include "db/quote/quote.cpp" // DB::Quote
#include "five_min_candle.h"  // DB::FiveMinCandle
#include "lib/pg/pg.cpp"      // Pg
#include <string>             // std::string

DB::FiveMinCandle::FiveMinCandle(const Pg c, const std::string symbol_) {
  this->conn = c;
  this->symbol = symbol_;

  this->db_quote = DB::Quote(this->conn);
}

#endif
