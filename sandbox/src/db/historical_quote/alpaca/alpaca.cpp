#ifndef DB__HISTORICAL_QUOTE__ALPACA
#define DB__HISTORICAL_QUOTE__ALPACA

#include "alpaca.h" // DB::HistoricalQuote::Alpaca, Base, init_args_t
#include "alpaca/client/client.cpp" // ::Alpaca::Client

#include "fetch_historical_quotes.cpp"
#include "prepare_for_upsert.cpp"

DB::HistoricalQuote::Alpaca::Alpaca(const init_args_t a) : Base(a) {
  this->api_client = ::Alpaca::Client(this->conn.flags);
}

#endif
