#ifndef DB__FIVE_MIN_CANDLES
#define DB__FIVE_MIN_CANDLES

#include "five_min_candles.h" // DB::FiveMinCandles
#include "build.cpp"
#include "db/quote/quote.cpp" // DB::Quote
#include "lib/pg/pg.cpp"      // Pg
#include <string>             // std::string

DB::FiveMinCandles::FiveMinCandles(const Pg c, const std::string symbol_) {
  this->conn = c;
  this->symbol = symbol_;

  this->db_quote = DB::Quote(this->conn);
}

#endif
