#ifndef DB__HISTORICAL_QUOTE__OANDA
#define DB__HISTORICAL_QUOTE__OANDA

#include "oanda.h" // DB::HistoricalQuote::Oanda, Base, init_args_t
#include "oanda/client/client.cpp" // ::Oanda::Client

#include "fetch_historical_quotes.cpp"
#include "prepare_for_upsert.cpp"

DB::HistoricalQuote::Oanda::Oanda(const init_args_t a) : Base(a) {
  this->api_client = ::Oanda::Client(this->conn.flags);
}

#endif
