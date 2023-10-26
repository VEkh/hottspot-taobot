#ifndef DB__CANDLE
#define DB__CANDLE

#include "candle.h" // DB::Candle
#include "build.cpp"
#include "db/quote/quote.cpp" // DB::Quote
#include "get_latest.cpp"
#include "lib/pg/pg.cpp" // Pg
#include <string>        // std::string

DB::Candle::Candle(const Pg c, const int duration_minutes_,
                   const std::string symbol_) {
  this->conn = c;
  this->duration_minutes = duration_minutes_;
  this->symbol = symbol_;

  this->db_quote = DB::Quote(this->conn);
}

#endif