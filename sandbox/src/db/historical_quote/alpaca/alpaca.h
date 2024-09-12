#ifndef DB__HISTORICAL_QUOTE__ALPACA_H
#define DB__HISTORICAL_QUOTE__ALPACA_H

#include "alpaca/client/client.cpp" // ::Alpaca::Client
#include "db/historical_quote/base/base.cpp" // DB::HistoricalQuote::Base, init_args_t, quote_t
#include "deps.cpp"                          // json

namespace DB {
namespace HistoricalQuote {
using Base = DB::HistoricalQuote::Base;

class Alpaca : public Base {
public:
  Alpaca(){};
  Alpaca(const init_args_t);

private:
  ::Alpaca::Client api_client;

  json fetch_historical_quotes() override;

  quote_t prepare_for_upsert(json &) override;
};
} // namespace HistoricalQuote
} // namespace DB

#endif
